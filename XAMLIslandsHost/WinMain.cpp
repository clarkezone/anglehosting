#include "pch.h"
#include "DesktopWindow.h"

extern "C" IMAGE_DOS_HEADER __ImageBase;

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI;
using namespace Windows::UI::Composition;
using namespace Windows::UI::Xaml::Hosting;
using namespace Windows::Foundation::Numerics;

struct Window : DesktopWindow<Window>
{
	Window() noexcept
	{
		WNDCLASS wc{};
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hInstance = reinterpret_cast<HINSTANCE>(&__ImageBase);
		wc.lpszClassName = L"XAML island in Win32";
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		RegisterClass(&wc);
		WINRT_ASSERT(!m_window);

		WINRT_VERIFY(CreateWindow(wc.lpszClassName,
			L"XAML island in Win32",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			nullptr, nullptr, wc.hInstance, this));

		WINRT_ASSERT(m_window);

		m_manager = InitXaml(m_window, m_rootGrid, m_xamlSource);
	}

	~Window() {
		m_manager.Close();
	}

	Windows::UI::Xaml::Hosting::WindowsXamlManager InitXaml(
		HWND wind,
		Windows::UI::Xaml::Controls::Grid& root,
		DesktopWindowXamlSource& source) {

		auto manager = Windows::UI::Xaml::Hosting::WindowsXamlManager::InitializeForCurrentThread();

		// Create the desktop source
		DesktopWindowXamlSource desktopSource;
		auto interop = desktopSource.as<IDesktopWindowXamlSourceNative>();
		check_hresult(interop->AttachToWindow(wind));

		// stash the interop handle so we can resize it when the main hwnd is resized
		HWND h = nullptr;
		interop->get_WindowHandle(&h);
		m_interopWindowHandle = h;

		// setup a root grid
		Windows::UI::Xaml::Controls::Grid rootGrid;
		Windows::UI::Xaml::Media::SolidColorBrush background{ Windows::UI::Colors::White() };

		// Set the content of the rootgrid to the DPI scaling grid
		desktopSource.Content(rootGrid);

		// Update the window size, DPI layout correction
		OnSize(h, rootGrid, m_currentWidthPhysical, m_currentHeightPhysical);

		// set out params
		root = rootGrid;
		source = desktopSource;
		return manager;
	}

	void OnSize(HWND interopHandle,
		winrt::Windows::UI::Xaml::Controls::Grid& rootGrid,
		UINT physicalWidth,
		UINT physicalHeight) {

		// update the interop window size to the physical window size
		SetWindowPos(interopHandle, 0, 0, 0, physicalWidth, physicalHeight, SWP_SHOWWINDOW);

		// Store current physical width and height
		m_currentWidthPhysical = physicalWidth;
		m_currentHeightPhysical = physicalHeight;

		// calculate logical width height and update the root grid to that
		auto scaleFactor = (float)m_currentDpi / 100;

		if (rootGrid != nullptr) {
			rootGrid.Width(physicalWidth / scaleFactor);
			rootGrid.Height(physicalHeight / scaleFactor);
		}
	}

	LRESULT MessageHandler(UINT const message, WPARAM const wparam, LPARAM const lparam) noexcept
	{
		// TODO: handle messages here...
		return base_type::MessageHandler(message, wparam, lparam);
	}

	void DoResize(UINT width, UINT height) {
		OnSize(m_interopWindowHandle, m_rootGrid, width, height);
	}

	void SetRootContent(Windows::UI::Xaml::UIElement content) {
		m_rootGrid.Children().Clear();
		m_rootGrid.Children().Append(content);
	}

private:
	UINT m_currentWidthPhysical = 600;
	UINT m_currentHeightPhysical = 600;
	HWND m_interopWindowHandle = nullptr;
	Windows::UI::Xaml::Controls::Grid m_rootGrid{ nullptr };
	DesktopWindowXamlSource m_xamlSource{ nullptr };
	Windows::UI::Xaml::Hosting::WindowsXamlManager m_manager{ nullptr };
};

Windows::UI::Xaml::UIElement CreateDefaultContent() {

	Windows::UI::Xaml::Media::AcrylicBrush acrylicBrush;
	acrylicBrush.BackgroundSource(Windows::UI::Xaml::Media::AcrylicBackgroundSource::HostBackdrop);
	acrylicBrush.TintOpacity(0.5);
	acrylicBrush.TintColor(Windows::UI::Colors::Red());

	Windows::UI::Xaml::Controls::Grid container;
	container.Margin(Windows::UI::Xaml::ThicknessHelper::FromLengths(100, 100, 100, 100));
	/*container.Background(Windows::UI::Xaml::Media::SolidColorBrush{ Windows::UI::Colors::LightSlateGray() });*/
	container.Background(acrylicBrush);

	Windows::UI::Xaml::Controls::Button b;
	b.Width(600);
	b.Height(60);
	b.SetValue(Windows::UI::Xaml::FrameworkElement::VerticalAlignmentProperty(),
		box_value(Windows::UI::Xaml::VerticalAlignment::Center));

	b.SetValue(Windows::UI::Xaml::FrameworkElement::HorizontalAlignmentProperty(),
		box_value(Windows::UI::Xaml::HorizontalAlignment::Center));
	b.Foreground(Windows::UI::Xaml::Media::SolidColorBrush{ Windows::UI::Colors::White() });

	Windows::UI::Xaml::Controls::TextBlock tb;
	tb.Text(L"Hello Win32 love XAML and C++/WinRT xx");
	b.Content(tb);
	tb.FontSize(30.0f);
	container.Children().Append(b);

	Windows::UI::Xaml::Controls::TextBlock dpitb;
	dpitb.Text(L"(p.s. high DPI just got much easier for win32 devs)");
	dpitb.Foreground(Windows::UI::Xaml::Media::SolidColorBrush{ Windows::UI::Colors::White() });
	dpitb.Margin(Windows::UI::Xaml::ThicknessHelper::FromLengths(10, 10, 10, 10));
	dpitb.SetValue(Windows::UI::Xaml::FrameworkElement::VerticalAlignmentProperty(),
		box_value(Windows::UI::Xaml::VerticalAlignment::Bottom));

	dpitb.SetValue(Windows::UI::Xaml::FrameworkElement::HorizontalAlignmentProperty(),
		box_value(Windows::UI::Xaml::HorizontalAlignment::Right));
	container.Children().Append(dpitb);

	return container;
}

int __stdcall wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
	init_apartment(apartment_type::single_threaded);

	Window window;

	auto defaultContent = CreateDefaultContent();
	window.SetRootContent(defaultContent);

	MSG message;

	while (GetMessage(&message, nullptr, 0, 0))
	{
		DispatchMessage(&message);
	}
}
