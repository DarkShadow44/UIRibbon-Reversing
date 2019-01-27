#include <stdio.h>

#if __MINGW32__

#define INITGUID
#define COBJMACROS
#include "/usr/include/wine/windows/uiribbon.h"
#include "parser_generic.h"

typedef struct {
    IUIApplication IUIApplication_iface;
    LONG ref;
} IUIApplicationImpl;

static IUIApplicationImpl *impl_from_IUIApplication(IUIApplication *iface)
{
    return CONTAINING_RECORD(iface, IUIApplicationImpl, IUIApplication_iface);
}


static HRESULT WINAPI IUIApplicationImpl_QueryInterface(IUIApplication* iface, REFIID riid, void** ppvObject)
{
    IUIApplicationImpl *This = impl_from_IUIApplication(iface);

    if (IsEqualGUID(riid, &IID_IUnknown)
        || IsEqualGUID(riid, &IID_IUIApplication))
    {
        IUnknown_AddRef(iface);
        *ppvObject = &This->IUIApplication_iface;
        return S_OK;
    }

    return E_NOINTERFACE;
}

static ULONG WINAPI IUIApplicationImpl_AddRef(IUIApplication* iface)
{
    IUIApplicationImpl *This = impl_from_IUIApplication(iface);
    ULONG ref = InterlockedIncrement(&This->ref);

    return ref;
}

static ULONG WINAPI IUIApplicationImpl_Release(IUIApplication* iface)
{
    IUIApplicationImpl *This = impl_from_IUIApplication(iface);
    ULONG ref = InterlockedDecrement(&This->ref);

    if (!ref)
        HeapFree(GetProcessHeap(), 0, This);

    return ref;
}

static HRESULT WINAPI IUIApplicationImpl_OnViewChanged(IUIApplication* iface, UINT32 viewId, UI_VIEWTYPE typeID, IUnknown *view, UI_VIEWVERB verb, INT32 uReasonCode)
{
    return S_OK;
}

static HRESULT WINAPI IUIApplicationImpl_OnCreateUICommand(IUIApplication* iface, UINT32 commandId, UI_COMMANDTYPE typeID, IUICommandHandler **commandHandler)
{
    return S_OK;
}


static HRESULT WINAPI IUIApplicationImpl_OnDestroyUICommand(IUIApplication* iface, UINT32 commandId, UI_COMMANDTYPE typeID, IUICommandHandler *commandHandler)
{
    return S_OK;
}


static IUIApplicationVtbl IUIApplication_Vtbl =
{
    IUIApplicationImpl_QueryInterface,
    IUIApplicationImpl_AddRef,
    IUIApplicationImpl_Release,
    IUIApplicationImpl_OnViewChanged,
    IUIApplicationImpl_OnCreateUICommand,
    IUIApplicationImpl_OnDestroyUICommand
};

static void IUIApplicationImpl_Create(IUIApplicationImpl** impl)
{
    IUIApplicationImpl* object;

    object = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IUIApplicationImpl));

    object->IUIApplication_iface.lpVtbl = &IUIApplication_Vtbl;
    object->ref = 1;

    *impl = object;
}


static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE)
                PostQuitMessage(0);
            break;
        default:
            return DefWindowProcA(hWnd, msg, wParam, lParam);
    }

    return 0;
}

int patch_file(const char *name)
{
    HANDLE handle;
    const test_data *test;

    handle = BeginUpdateResource("../../_DLL/dll.dll", FALSE);
    if (!handle)
    {
        printf("Failed to load test dll: %d\n", (int)GetLastError());
        return 1;
    }

    test = get_test_data(name);
    if (!test)
    {
        printf("Failed to load test data\n");
        return 1;
    }

    UpdateResourceA(handle, "UIFILE", "APPLICATION_RIBBON", MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), (void *)test->bml_data, test->bml_len);

    EndUpdateResourceA(handle, FALSE);
    return 0;
}

int run_visual_test(const char *name)
{
    WNDCLASSA wc = {0};
    HWND handle_window;
    MSG msg;
    HRESULT hr;
    IUIFramework *framework;
    IUIApplication *application;
    IUIApplicationImpl *application_impl;
	HINSTANCE instance;
    static const WCHAR str_ribbonres[] = {'A','P','P','L','I','C','A','T','I','O','N','_','R','I','B','B','O','N',0};

    patch_file(name);

	instance = LoadLibraryA("../../_DLL/dll.dll");
	if (!instance)
    {
        MessageBoxA(NULL, "Failed to load test dll!", "", 0);
        return 1;
    }

    CoInitialize(NULL);

    wc.hInstance = GetModuleHandleA(NULL);
    wc.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
    wc.lpszClassName = "Test";
    wc.lpfnWndProc = MainWndProc;
    RegisterClassA(&wc);

    handle_window = CreateWindowA("Test", "", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 400, 400, NULL, NULL, NULL, 0);

    hr = CoCreateInstance(&CLSID_UIRibbonFramework, NULL, CLSCTX_INPROC_SERVER, &IID_IUIFramework, (void **)&framework);
    if (FAILED(hr))
    {
        printf("CoCreateInstance failed.\n");
        return 0;
    }

    IUIApplicationImpl_Create(&application_impl);
    application = &application_impl->IUIApplication_iface;

    hr = IUIFramework_Initialize(framework, handle_window, application);
    if (FAILED(hr))
    {
        printf("IUIFramework_Initialize failed.\n");
        return 0;
    }

    hr = IUIFramework_LoadUI(framework, instance, str_ribbonres);
    if (FAILED(hr))
    {
        printf("IUIFramework_LoadUI failed.\n");
        return 0;
    }

    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
#endif
