#include "buffer.h"

#include "eventfilter.h"
#include <QAbstractEventDispatcher>
#include <QSettings>

const int Buffer::HOTKEY_CODE = 100;

Buffer::Buffer() {}

void Buffer::registerHotKey(const WId winId, const char key) {
  RegisterHotKey((HWND)winId, // Set the system identifier of the widget
                              // window that will handle the HotKey
                 HOTKEY_CODE, // Set identifier HotKey
                 MOD_CONTROL | MOD_SHIFT | MOD_ALT, // Set modifiers
                 key);
}

const QString Buffer::getFocusAppName() {
  auto focused = GetForegroundWindow();

  DWORD dwProcId = 0;
  DWORD bufSize = MAX_PATH;
  CHAR buffer[MAX_PATH];

  GetWindowThreadProcessId(focused, &dwProcId);

  const auto handle =
      OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcId);
  QueryFullProcessImageNameA(handle, FALSE, buffer, &bufSize);

  const QString str = QString::fromUtf8(buffer);
  const auto appName = str.split("\\").back().split('.').front();

  return appName;
}

const bool Buffer::sendInput(const QString text) {
  std::wstring wText = text.toStdWString();

  std::vector<INPUT> vec;
  for (auto char_ : wText) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.dwFlags = KEYEVENTF_UNICODE;
    input.ki.wScan = char_;
    vec.push_back(input);

    input.ki.dwFlags |= KEYEVENTF_KEYUP;
    vec.push_back(input);
  }

  const auto inputRes = SendInput(vec.size(), vec.data(), sizeof(INPUT));
  const auto res = inputRes == vec.size();

  return res;
}

void Buffer::setEventListner(const QString propText) {
  QAbstractEventDispatcher::instance()->installNativeEventFilter(
      new EventFilter(propText));
}

const QList<QString> Buffer::getAcceptedApps() {

  const QSettings browsersRegList(
      "HKEY_LOCAL_MACHINE\\SOFTWARE\\Clients\\StartMenuInternet",
      QSettings::NativeFormat);
  const QStringList browsersInRegList = browsersRegList.childGroups();

  QStringList res;
  for (auto browser : browsersInRegList) {

    const QString path =
        "HKEY_LOCAL_MACHINE\\SOFTWARE\\Clients\\StartMenuInternet\\" + browser +
        "\\shell\\open\\command";
    const QSettings openBrowser(path, QSettings::NativeFormat);

    const auto browserExe = openBrowser.value(".");
    auto browserExeStr = browserExe.toString();
    browserExeStr.chop(1);

    const auto finalBrowserStr =
        browserExeStr.split("\\").back().split('.').front();

    res.append(finalBrowserStr);
  }

  return res;
}

const bool Buffer::isAppAccepted(const QString appName) {
  return getAcceptedApps().contains(appName);
}
