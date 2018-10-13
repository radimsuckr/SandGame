#include "CMainWindow.hpp"
#include <memory>

int main() {
	std::unique_ptr<CMainWindow> window(new CMainWindow());

    return window->execute();
}
