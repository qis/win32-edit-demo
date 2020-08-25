#include <version.h>

class CustomEdit : public CWindowImpl<CustomEdit, CEdit> {
public:
  BEGIN_MSG_MAP(CustomEdit)
    MSG_WM_CHAR(OnChar)
  END_MSG_MAP()

  void OnChar(TCHAR c, UINT count, UINT flags) {
    if (c == 'X' || c == 'c') {
      return;
    }
    SetMsgHandled(FALSE);
  }
};

class Application : public CDialogImpl<Application> {
public:
  static constexpr DWORD IDD = IDD_APPLICATION;

  BEGIN_MSG_MAP_EX(Application)
    MSG_WM_INITDIALOG(OnInitDialog)
    MSG_WM_DESTROY(OnDestroy)
    MSG_WM_CLOSE(OnClose)
  END_MSG_MAP()

  LRESULT OnInitDialog(HWND hwnd, LPARAM lparam) {
    SetWindowText(PROJECT_DESCRIPTION);
    SetIcon(LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDD)));
    edit_.SubclassWindow(GetDlgItem(IDC_EDIT));
    return TRUE;
  }

  void OnClose() {
    DestroyWindow();
  }

  void OnDestroy() {
    PostQuitMessage(EXIT_SUCCESS);
  }

private:
  CustomEdit edit_;
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, PSTR cmd, int show) {
  int result = EXIT_SUCCESS;
  try {
    const INITCOMMONCONTROLSEX icc = { sizeof(icc), ICC_WIN95_CLASSES };
    if (!InitCommonControlsEx(&icc)) {
      throw std::runtime_error("Could not initialize common controls.");
    }

    if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
      throw std::runtime_error("Could not initialize ATL.");
    }

    Application application;
    application.Create(nullptr);
    application.ShowWindow(show);

    CMessageLoop loop;
    result = loop.Run();
  }
  catch (const std::exception& e) {
    MessageBox(nullptr, e.what(), PROJECT_DESCRIPTION, MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
    result = EXIT_FAILURE;
  }
  CoUninitialize();
  return result;
}
