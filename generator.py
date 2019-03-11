# Is python ok ? Which langauges allowed? Generate writer + reader get rid of C#


import yaml

with open("new.ksy", 'r') as stream:
    try:
        print(yaml.load(stream))
    except yaml.YAMLError as exc:
        print(exc)
