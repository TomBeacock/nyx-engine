#pragma once

#include "nyx/types.h"

#include <memory>
#include <string>

namespace Nyx {
class Event;
class WindowImpl;
class Renderer;
}  // namespace Nyx

namespace Nyx {
class Window {
  public:
    Window();
    Window(const Window &) = delete;
    Window(const Window &&) = delete;
    ~Window();

    Window &operator=(const Window &) = delete;
    Window &operator=(const Window &&) = delete;

    /**
     * @brief Update the window.
     */
    void update();

    /**
     * @brief Present the next frame.
     */
    void present();

    /**
     * @brief Show the window.
     */
    void show();

    /**
     * @brief Maximise the window to fill screen.
     */
    void maximise();

    /**
     * @brief Minimise the window to the taskbar.
     */
    void minimise();

    /**
     * @brief Restore the window to previous size.
     */
    void restore();

    /**
     * @brief Poll the window for the next event.
     *
     * @return The polled event.
     */
    Event poll_event();

    /**
     * @brief Set the window's title.
     *
     * @param title UTF-8 encoded string.
     */
    void set_title(const std::u8string &title);

    /**
     * @brief Set the cursor's visibility.
     *
     * @param visible Should the cursor be visible.
     */
    void set_cursor_visibility(bool visible);

    /**
     * @brief Get the width of the client area of the window
     */
    uint32_t get_client_width() const;

    /**
     * @brief Get the height of the client area of the window
     */
    uint32_t get_client_height() const;

    /**
     * @brief Get the underlying platform implementation
     *
     * @return The platform implmentatioin
     */
    const WindowImpl &get_impl() const;

  private:
    void filter_event(const Event &event);

  private:
    std::unique_ptr<WindowImpl> window_impl;
    std::unique_ptr<Renderer> renderer;
    Nat32 width, height;
};
}  // namespace Nyx