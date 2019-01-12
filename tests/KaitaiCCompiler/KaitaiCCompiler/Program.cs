using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using YamlDotNet;
using YamlDotNet.RepresentationModel;
using System.IO;
using System.Globalization;
using System.Text.RegularExpressions;

namespace KaitaiCCompiler
{
    class Program
    {
        class TypeInfo
        {
            public string Name;
            public SeqInfo seqInfo = new SeqInfo();
        }

        class TypeSwitchInfo
        {
            public string enumname;
            public string type;
            public string unionname;
        }

        class SeqInfo
        {
            public List<string> linesCode = new List<string>();
            public List<string> linesVar = new List<string>();
            public List<string> linesStruct = new List<string>();
            public List<string> dependencies = new List<string>();
            public bool hasI = false;
            private int indentCode = 1;
            private int indentStruct = 1;

            public void AddCode(string format, params object[] par)
            {
                var tabs = new string('\t', indentCode);
                linesCode.Add(tabs + string.Format(format, par));
            }

            public void AddVar(string format, params object[] par)
            {
                linesVar.Add("\t" + string.Format(format, par));
            }

            public void AddStruct(string format, params object[] par)
            {
                var tabs = new string('\t', indentStruct);
                var newLine = tabs + string.Format(format, par);
                if (!linesStruct.Contains(newLine))
                    linesStruct.Add(newLine);
            }

            public void AddDependency(string type)
            {
                if (type == "uint8_t" || type == "uint16_t" || type == "uint32_t")
                    return;

                if (dependencies.Contains(type))
                    return;

                dependencies.Add(type);
            }

            public void IndentCodePlus()
            {
                indentCode++;
            }

            public void IndentCodeMinus()
            {
                indentCode--;
            }

            public void IndentStructPlus()
            {
                indentStruct++;
            }

            public void IndentStructMinus()
            {
                indentStruct--;
            }
        }

        class EnumInfo
        {
            public string Name;
            public List<string> linesEnum = new List<string>();

            public void Add(string format, params object[] par)
            {
                linesEnum.Add("\t" + string.Format(format, par));
            }
        }

        static string getTypeIdentifier(string ident)
        {
            switch (ident)
            {
                case "u1":
                    return "uint8_t";
                case "u2":
                    return "uint16_t";
                case "u4":
                    return "uint32_t";
            }
            return null;
        }

        static bool isSpecialChar(char c)
        {
            switch (c)
            {
                case ' ':
                case '+':
                case '-':
                case '*':
                case '/':
                case '&':
                case '|':
                case '(':
                case ')':
                    return true;
            }
            return false;
        }

        static string[] splitExpression(string expr)
        {
            List<int> posSplit = new List<int>();
            List<string> ret = new List<string>();
            for (int i = 1; i < expr.Length; i++)
            {
                char current = expr[i];
                char last = expr[i - 1];

                if (isSpecialChar(current) && !isSpecialChar(last) || !isSpecialChar(current) && isSpecialChar(last))
                {
                    posSplit.Add(i);
                }
            }
            posSplit.Add(expr.Length);

            for (int i = 0; i < posSplit.Count; i++)
            {
                int start;
                if (i == 0)
                    start = 0;
                else
                    start = posSplit[i - 1];
                int end = posSplit[i];

                string str = expr.Substring(start, end - start).Trim();
                if (str.Length > 0)
                    ret.Add(str);
            }

            return ret.ToArray();
        }

        static string prefixExpression(string expr)
        {
            expr = expr.Replace(" or ", " || ");
            expr = expr.Replace(" and ", " && ");
            string[] parts = splitExpression(expr);

            for (int i = 0; i < parts.Length; i++)
            {
                if (parts[i].Contains("::"))
                {
                    var split = parts[i].Split(new string[] { "::" }, StringSplitOptions.None);
                    parts[i] = makeEnumName(split[0], split[1]);
                }

                if (parts[i] == "true")
                    parts[i] = "1";
                if(parts[i] == "false")
                    parts[i] = "0";

                if (char.IsLetter(parts[i][0]) && char.IsLower(parts[i][0]))
                {
                    parts[i] = "ret->" + parts[i];
                }
            }
            expr = string.Join(" ", parts);
            expr = expr.Replace("_.", "##current##->");
            expr = expr.Replace("( ", "(");
            expr = expr.Replace(" )", ")");
            return expr;
        }

        static int parseInt(string s)
        {
            if (s.Contains("x"))
                return int.Parse(s.Substring(2), NumberStyles.AllowHexSpecifier);
            else
                return int.Parse(s);
        }

        static SeqInfo buildSeq(YamlSequenceNode node)
        {
            var ret = new SeqInfo();
            foreach (var child in node.Children)
            {
                string id = null;
                List<byte> contents = null;
                string type = null;
                string repeat = null;
                string repeat_expr = null;
                string size = null;
                string condition = null;
                string enum_type = null;
                string type_switch_on = null;
                string repeat_until = null;
                List<TypeSwitchInfo> type_switch_info = null;
                foreach (var map in ((YamlMappingNode)child).Children)
                {
                    var key = ((YamlScalarNode)map.Key).Value;
                    if (key == "id")
                    {
                        id = ((YamlScalarNode)map.Value).Value;
                    }
                    if (key == "contents")
                    {
                        contents = new List<byte>();
                        if (map.Value.NodeType == YamlNodeType.Scalar)
                        {
                            var val = ((YamlScalarNode)map.Value).Value;
                            contents.AddRange(Encoding.ASCII.GetBytes(val));
                        }
                        else
                        {
                            foreach (var val in ((YamlSequenceNode)map.Value).Children)
                            {
                                var num = ((YamlScalarNode)val).Value;
                                contents.Add((byte)parseInt(num));
                            }
                        }
                    }
                    if (key == "type")
                    {
                        if (map.Value.NodeType == YamlNodeType.Scalar)
                        {
                            type = ((YamlScalarNode)map.Value).Value;
                        }
                        else
                        {
                            var typeMap = (YamlMappingNode)map.Value;
                            foreach (var typeMapPart in typeMap.Children)
                            {
                                var key2 = ((YamlScalarNode)typeMapPart.Key).Value;

                                if (key2 == "switch-on")
                                {
                                    type_switch_on = ((YamlScalarNode)typeMapPart.Value).Value;
                                    type_switch_on = prefixExpression(type_switch_on);
                                }

                                if (key2 == "cases")
                                {
                                    type_switch_info = new List<TypeSwitchInfo>();
                                    foreach (var typeCase in ((YamlMappingNode)typeMapPart.Value).Children)
                                    {
                                        var key3 = ((YamlScalarNode)typeCase.Key).Value;
                                        var val3 = ((YamlScalarNode)typeCase.Value).Value;

                                        TypeSwitchInfo info = new TypeSwitchInfo();
                                        type_switch_info.Add(info);
                                        info.enumname = prefixExpression(key3);
                                        info.type = val3;

                                        if (key3.Contains("::"))
                                        {
                                            var split = key3.Split(new string[] { "::" }, StringSplitOptions.None);
                                            info.unionname = "block_" + split[1];
                                        }
                                        else
                                        {
                                            info.unionname = "block_" + key3;
                                        }

                                        var typeind2 = getTypeIdentifier(info.type);
                                        if (typeind2 != null)
                                            info.type = typeind2;
                                    }
                                }
                            }
                        }
                    }
                    if (key == "repeat")
                    {
                        repeat = ((YamlScalarNode)map.Value).Value;
                    }
                    if (key == "repeat-expr")
                    {
                        repeat_expr = ((YamlScalarNode)map.Value).Value;
                        repeat_expr = prefixExpression(repeat_expr);
                    }
                    if (key == "repeat-until")
                    {
                        repeat_until = ((YamlScalarNode)map.Value).Value;
                        repeat_until = prefixExpression(repeat_until);
                    }
                    if (key == "size")
                    {
                        size = ((YamlScalarNode)map.Value).Value;
                        size = prefixExpression(size);
                    }
                    if (key == "if")
                    {
                        condition = ((YamlScalarNode)map.Value).Value;
                        condition = prefixExpression(condition);
                    }
                    if (key == "enum")
                    {
                        enum_type = ((YamlScalarNode)map.Value).Value;
                    }
                }

                var typeind = getTypeIdentifier(type);
                if (typeind != null)
                    type = typeind;

                if (condition != null)
                {
                    ret.AddCode("if ({0})", condition);
                    ret.AddCode("{{");
                    ret.IndentCodePlus();
                }

                if (contents != null)
                {
                    var bytes = string.Join(", ", contents.ToArray());
                    ret.AddVar("const char {0}[] = {{{1}}};", id, bytes);
                    ret.AddCode("CHECK(stream_expect_bytes(s, {0}));", id);
                }
                else
                {
                    if (repeat != null && repeat == "expr")
                    {
                        ret.AddStruct("{0} *{1};", type, id);
                        ret.AddDependency(type);
                        ret.hasI = true;
                        ret.AddCode("ret->{0} = malloc(sizeof({1}) * {2});", id, type, repeat_expr);
                        ret.AddCode("for (i = 0; i < {0}; i++)", repeat_expr);
                        ret.AddCode("{{");
                        ret.IndentCodePlus();
                        ret.AddCode("CHECK(read_{0}(s_root, s, &ret->{1}[i]));", type, id);
                        ret.IndentCodeMinus();
                        ret.AddCode("}}");
                    }
                    else if (repeat != null && repeat == "until")
                    {
                        ret.AddStruct("{0} *{1};", type, id);
                        ret.AddDependency(type);
                        ret.hasI = true;
                        ret.AddCode("ret->{0} = NULL;", id);
                        ret.AddCode("i = -1;");
                        ret.AddCode("do");
                        ret.AddCode("{{");
                        ret.IndentCodePlus();
                        ret.AddCode("i++;");
                        ret.AddCode("ret->{0} = realloc(ret->{0}, sizeof({1}) * i);", id, type);
                        ret.AddCode("CHECK(read_{0}(s_root, s, &ret->{1}[i]));", type, id);
                        ret.IndentCodeMinus();
                        var repeat_cond = repeat_until.Replace("##current##->", "ret->{0}[i].");
                        repeat_cond = string.Format(repeat_cond, id);
                        ret.AddCode("}} while(!({0}));", repeat_cond);
                    }
                    else if (size != null)
                    {
                        if (type == null || type == "str")
                        {
                            ret.AddStruct("char *{0};", id);
                            ret.AddCode("ret->{0} = malloc({1});", id, size);
                            ret.AddCode("CHECK(stream_read_bytes(s, ret->{0}, {1}));", id, size);
                        }
                        else
                        {
                            ret.AddStruct("{0} {1};", type, id);
                            ret.AddDependency(type);
                            ret.AddVar("stream substream_{0};", id);
                            ret.AddCode("CHECK(stream_make_substream(s, &substream_{0}, {1}));", id, size);
                            ret.AddCode("CHECK(read_{0}(s_root, &substream_{1}, &ret->{1}));", type, id);
                        }
                    }
                    else if (type_switch_on != null)
                    {
                        bool isInt = type_switch_info[0].type.StartsWith("uint");
                        if (isInt)
                            ret.AddStruct("uint32_t {0};", id);
                        else
                        {
                            ret.AddStruct("union");
                            ret.AddStruct("{{");
                            ret.IndentStructPlus();
                        }
                        ret.AddCode("switch({0})", type_switch_on);
                        ret.AddCode("{{");

                        foreach (var info in type_switch_info)
                        {
                            if (isInt)
                                ret.AddVar("{0} {1}_{2};", info.type, id, info.unionname);
                            else
                                ret.AddStruct("{0} {1};", info.type, info.unionname);
                            ret.AddDependency(info.type);
                            ret.AddCode("case {0}:", info.enumname);
                            ret.IndentCodePlus();
                            if (info.type.StartsWith("uint"))
                            {
                                ret.AddCode("CHECK(stream_read_{0}(s, &{2}_{1}));", info.type, info.unionname, id);
                                ret.AddCode("ret->{0} = {0}_{1};", id, info.unionname);
                            }
                            else
                                ret.AddCode("CHECK(read_{0}(s_root, s, &ret->{1}));", info.type, info.unionname);
                            ret.AddCode("break;");
                            ret.IndentCodeMinus();
                        }
                        ret.AddCode("}}");
                        if (!isInt)
                        {
                            ret.IndentStructMinus();
                            ret.AddStruct("}};");
                        }
                    }
                    else if (enum_type != null)
                    {
                        ret.AddVar("{0} {1};", type, id);
                        ret.AddStruct("{0} {1};", enum_type, id);
                        if (type.StartsWith("uint"))
                            ret.AddCode("CHECK(stream_read_{0}(s, &{1}));", type, id);
                        else
                            ret.AddCode("CHECK(read_{0}(s_root, s, &{1}));", type, id);
                        ret.AddCode("ret->{0} = {0};", id);
                    }
                    else if(type != null)
                    {
                        ret.AddStruct("{0} {1};", type, id);
                        ret.AddDependency(type);
                        if (type.StartsWith("uint"))
                            ret.AddCode("CHECK(stream_read_{0}(s, &ret->{1}));", type, id);
                        else
                            ret.AddCode("CHECK(read_{0}(s_root, s, &ret->{1}));", type, id);
                    }
                }

                if (condition != null)
                {
                    ret.IndentCodeMinus();
                    ret.AddCode("}}");
                }
            }

            return ret;
        }

        static void buildInstance(SeqInfo seq, YamlMappingNode node)
        {
            foreach (var _instance in node.Children)
            {
                var instance_key = (YamlScalarNode)_instance.Key;
                var instance_value = (YamlMappingNode)_instance.Value;

                string io = null;
                string pos = null;
                string type = null;
                string value = null;

                foreach (var _instanceinfo in instance_value.Children)
                {
                    var instanceinfo_key = (YamlScalarNode)_instanceinfo.Key;
                    var instanceinfo_value = (YamlScalarNode)_instanceinfo.Value;

                    if (instanceinfo_key.Value == "io")
                    {
                        io = instanceinfo_value.Value;
                    }

                    if (instanceinfo_key.Value == "pos")
                    {
                        pos = prefixExpression(instanceinfo_value.Value);
                    }

                    if (instanceinfo_key.Value == "type")
                    {
                        type = instanceinfo_value.Value;
                    }

                    if (instanceinfo_key.Value == "value")
                    {
                        value = prefixExpression(instanceinfo_value.Value);
                    }
                }

                if (value != null)
                {
                    seq.AddStruct("{0} {1};", "uint8_t", instance_key.Value);
                    seq.AddCode("ret->{0} = {1};", instance_key.Value, value);
                    continue;
                }

                if (io != "_root._io")
                {
                    throw new InvalidDataException();
                }

                seq.AddDependency(type);
                seq.AddStruct("{0} {1};", type, instance_key.Value);
                if (type.StartsWith("uint"))
                    seq.AddCode("CHECK(stream_read_{0}(s_root, &ret->{1}));", type, instance_key.Value);
                else
                    seq.AddCode("CHECK(read_{0}(s_root, s_root, &ret->{1}));", type, instance_key.Value);
            }
        }

        static List<TypeInfo> buildTypes(YamlMappingNode node)
        {
            var ret = new List<TypeInfo>();
            foreach (var type in node.Children)
            {
                TypeInfo info = new TypeInfo();
                ret.Add(info);

                info.Name = ((YamlScalarNode)type.Key).Value;
                foreach (var map in (YamlMappingNode)type.Value)
                {
                    var key = ((YamlScalarNode)map.Key).Value;
                    if (key == "seq")
                    {
                        info.seqInfo = buildSeq((YamlSequenceNode)map.Value);
                    }
                    if (key == "instances")
                    {
                        buildInstance(info.seqInfo, (YamlMappingNode)map.Value);
                    }
                }
            }
            return ret;
        }

        static string makeEnumName(string type, string name)
        {
            type = type.Trim();
            string ret = type + "_" + name;
            if (ret.StartsWith("enum_"))
                ret = ret.Substring(5);
            ret = "uiribbon_" + ret;
            return ret.ToUpper();
        }

        static List<EnumInfo> buildEnums(YamlMappingNode node)
        {
            var ret = new List<EnumInfo>();
            foreach (var currentEnum in node.Children)
            {
                EnumInfo info = new EnumInfo();
                ret.Add(info);

                info.Name = ((YamlScalarNode)currentEnum.Key).Value;
                foreach (var map in ((YamlMappingNode)currentEnum.Value).Children)
                {
                    var key = ((YamlScalarNode)map.Key).Value;
                    var val = ((YamlScalarNode)map.Value).Value;

                    string name = makeEnumName(info.Name, val);
                    info.Add("{0} = {1},", name, parseInt(key));
                }
            }
            return ret;
        }

        static int findTypeWithOkDependencies(List<TypeInfo> existing, List<TypeInfo> remaining)
        {
            for (int i = 0; i < remaining.Count; i++)
            {
                var currentToTest = remaining[i];
                bool allSatisfied = true;
                for (int j = 0; j < currentToTest.seqInfo.dependencies.Count; j++)
                {
                    var currentDep = currentToTest.seqInfo.dependencies[j];
                    bool found = false;
                    for (int k = 0; k < existing.Count; k++)
                    {
                        if (existing[k].Name == currentDep)
                            found = true;
                    }
                    if (!found)
                    {
                        allSatisfied = false;
                        break;
                    }
                }
                if (allSatisfied)
                    return i;
            }
            return -1;
        }

        static List<TypeInfo> sortTypes(List<TypeInfo> info)
        {
            List<TypeInfo> ret = new List<TypeInfo>();

            while (info.Count > 0)
            {
                var index = findTypeWithOkDependencies(ret, info);
                ret.Add(info[index]);
                info.RemoveAt(index);
            }

            return ret;
        }

        static void writeStruct(StringBuilder sb, string name, SeqInfo seq)
        {
            sb.AppendFormat("typedef struct\n");
            sb.AppendLine("{");
            foreach (var line in seq.linesStruct)
            {
                sb.AppendLine(line);
            }
            sb.AppendFormat("}} {0};\n\n", name);
        }

        static void writeMethod(StringBuilder sb, string name, SeqInfo seq)
        {
            sb.AppendFormat("int read_{0}(stream *s_root, stream *s, {0} *ret)\n", name);
            sb.AppendLine("{");
            foreach (var line in seq.linesVar)
            {
                sb.AppendLine(line);
            }
            if (seq.hasI)
                sb.AppendLine("\tint i;");
            if (seq.linesVar.Count > 0 || seq.hasI)
                sb.AppendLine();
            foreach (var line in seq.linesCode)
            {
                sb.AppendLine(line);
            }
            sb.AppendLine("\treturn 0;");
            sb.AppendLine("}");
            sb.AppendLine();
        }

        static void Main(string[] args)
        {
            var data = File.ReadAllText(@"E:\_Ramdisk\new.ksy");
            var reader = new StringReader(data);

            string main_type = "type_uiribbon";

            var yaml = new YamlStream();
            yaml.Load(reader);

            var root = (YamlMappingNode)yaml.Documents[0].RootNode;

            List<EnumInfo> enums = null;
            SeqInfo mainSeq = null;
            List<TypeInfo> types = null;

            foreach (var child in root.Children)
            {
                var key = ((YamlScalarNode)child.Key).Value;

                if (key == "seq")
                {
                    mainSeq = buildSeq((YamlSequenceNode)child.Value);
                }

                if (key == "types")
                {
                    types = buildTypes((YamlMappingNode)child.Value);
                }

                if (key == "enums")
                {
                    enums = buildEnums((YamlMappingNode)child.Value);
                }
            }

            types = sortTypes(types);

            StringBuilder header = new StringBuilder();
            StringBuilder source = new StringBuilder();

            header.AppendLine("/* This file is generated - Do not edit manually */");
            header.AppendLine();
            header.AppendLine("#include \"parser_generic.h\"");
            header.AppendLine();
            foreach (var currentEnum in enums)
            {
                header.AppendFormat("typedef enum\n");
                header.AppendLine("{");
                foreach (var line in currentEnum.linesEnum)
                {
                    header.AppendLine(line);
                }
                header.AppendFormat("}} {0};\n\n", currentEnum.Name);
            }
            foreach (var type in types)
            {
                writeStruct(header, type.Name, type.seqInfo);
            }
            writeStruct(header, main_type, mainSeq);
            header.AppendFormat("int read_{0}(stream *s_root, stream *s, {0} *ret);\n", main_type);


            source.AppendLine("/* This file is generated - Do not edit manually */");
            source.AppendLine();
            source.AppendLine("#include \"parser_uiribbon.h\"");
            source.AppendLine();
            foreach (var type in types)
            {
                writeMethod(source, type.Name, type.seqInfo);
            }
            writeMethod(source, main_type, mainSeq);

            File.WriteAllText(@"E:\_Ramdisk\parser_uiribbon.h", header.ToString());
            File.WriteAllText(@"E:\_Ramdisk\parser_uiribbon.c", source.ToString());
        }
    }
}
