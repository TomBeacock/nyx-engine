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

    /**
     * Get the width of the client area of the window
     */
    uint32_t get_client_width() const;

    /**
     * Get the height of the client area of the window
     */
    uint32_t get_client_height() const;

    /**
     * Get the underlying platform implementation
     *
     * @return The platform implmentatioin
     */
    const WindowImpl &get_impl() const;

  private:
    void filter_event(const Event &event);

  private:
    std::unique_ptr<WindowImpl> window_impl;
    uint32_t width, height;
};
}  // namespace Nyx