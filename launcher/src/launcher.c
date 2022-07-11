
#include <platform/nav_window.h>
#include <platform/win32/win32_nav_window_struct.h>
#include <nav_debug.h>
#include <dxgi.h>
#include <d3d11.h>

int main(int argc, char** argv)
{
    Window* wnd = NavCreateWindow("nav", 600, 400);

    DXGI_SWAP_CHAIN_DESC swapChainDesc = {0};
    swapChainDesc.BufferDesc.Width = 600;
    swapChainDesc.BufferDesc.Height = 400;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 2;
    swapChainDesc.OutputWindow = wnd->hWnd;
    swapChainDesc.Windowed = 1;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


    ID3D11Device* iD3d11Dev;
    IDXGISwapChain* swapChain;
    ID3D11DeviceContext* iD3d11DevCtx;
    D3D_FEATURE_LEVEL featureLevel;


    D3D11CreateDevice(
        0,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        D3D11_CREATE_DEVICE_DEBUG,
        NULL,
        0,
        D3D11_SDK_VERSION,
        &iD3d11Dev,
        &featureLevel,
        &iD3d11DevCtx
    );

    //IDXGIDevice* iDxgiDev = 0;

    //iD3d11Dev->lpVtbl->QueryInterface(__declspec(uuid(IDXGIAdapter1)), (void**)&iDxgiDev);

    // HRESULT hRes = D3D11CreateDeviceAndSwapChain(
    //     (void*)0, 
    //     D3D_DRIVER_TYPE_HARDWARE,
    //     0,
    //     0,
    //     (void*)0,
    //     0,
    //     D3D11_SDK_VERSION,
    //     &swapChainDesc,
    //     &swapChain,
    //     &iD3d11Dev,
    //     0,
    //     &iD3d11DevCtx
    //     );

    DEBUG_LOG(DECIMAL_LOG_FORMAT, GREEN_CONSOLE_COLOR, IID_IDXGIAdapter);

    while(UpdateWindowEvents(wnd))
    {
        Sleep(10);
        //swapChain->lpVtbl->Present(swapChain, 1u, 0u);
    }

    NavDestroyWindow(wnd);

    iD3d11DevCtx->lpVtbl->Release(iD3d11DevCtx);
    //swapChain->lpVtbl->Release(swapChain);
    iD3d11Dev->lpVtbl->Release(iD3d11Dev);

    return 0;
}
