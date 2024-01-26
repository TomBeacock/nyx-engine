#pragma once

namespace Nyx {
class Event {
  public:
    enum Type {
        None = 0,
        Close = 1,
    };

  public:
    Event() = default;
    Event(const Event &e) = delete;
    ~Event() { delete this->data; }

    inline const Type &get_type() const { return this->type; }
    inline void set_type(Type type) { this->type = type; }

    template <typename T>
    inline T *get_data() const;

    template <typename T, typename... Args>
    inline void set_data(Args... args);

    Event &operator=(const Event &e) = delete;

  private:
    Type type = None;
    void *data = nullptr;
};

template <typename T>
inline T *Event::get_data() const
{
    return dynamic_cast<T *>(this->data);
}

template <typename T, typename... Args>
inline void Event::set_data(Args... args)
{
    delete this->data;
    this->data = new T(args);
}

}  // namespace Nyx