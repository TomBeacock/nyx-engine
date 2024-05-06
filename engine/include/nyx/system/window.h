#pragma once

#include <memory>
#include <string>

namespace Nyx {
class Event;
class WindowImpl;
}  // namespace Nyx

namespace Nyx {
class Window {
  public:
    Window();
    ~Window();

    /**
     * Show the window.
     */
    void show();

    /**
     * Maximise the window to fill screen.
     */
    void maximise();

    /**
     * Minimise the window to the taskbar.
     */
    void minimise();

    /**
     * Restore the window to previous size.
     */
    void restore();

    /**
     * Poll the window for the next event.
     *
     * @return The polled event.
     */
    Event poll_event();

    /**
     * Set the window's title.
     *
     * @param title UTF-8 encoded string.
     */
    void set_title(const std::u8string &title);

    /**
     * Set the cursor's visibility.
     *
     * @param visible Should the cursor be visible.
     */
    void set_cursor_visibility(bool visible);

  private:
    std::unique_ptr<WindowImpl> window_impl;
};
}  // namespace Nyx