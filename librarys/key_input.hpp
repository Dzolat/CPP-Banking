#if defined(__WIN32)
#include <conio.h>
#elif defined(__APPLE__) || defined(__linux__)
#include <termios.h>
#include <unistd.h>
#else
#error "Unsupported operating version"
#endif

namespace Input
{
    enum class Key
    {
        Unknown,
        Enter,
        Escape,
        Up,
        Down
    };

#ifdef _WIN32

    inline Key getkey()
    {
        const int first_key{_getch()};

        if (first_key == 13)
            return Key::Enter;

        if (first_key == 27)
            return Key::Escape;

        if (first_key == 0 || first_key == 224)
        {
            const int second_key{_getch()};

            switch (second_key)
            {
                case 72:
                    return Key::Up;

                case 80:

                return Key::Down;

                default:
                    return Key::Unknown;
            }
        }

        return Key::Unknown;
    }

#elif defined(__APPLE__) || defined(__linux__)
    //this code isnt made by me
    class TerminalRawMode
    {
    private:
        termios m_old_settings{};
        bool m_enabled{false};

    public:
        TerminalRawMode()
        {
            if (tcgetattr(STDIN_FILENO, &m_old_settings) != 0)
                return;

            termios new_settings{m_old_settings};

            new_settings.c_lflag &=
                static_cast<tcflag_t>(~(ICANON | ECHO));

            // Wait until at least one byte is available.
            new_settings.c_cc[VMIN] = 1;
            new_settings.c_cc[VTIME] = 0;

            if (tcsetattr(STDIN_FILENO, TCSANOW, &new_settings) == 0)
                m_enabled = true;
        }

        ~TerminalRawMode()
        {
            if (m_enabled)
                tcsetattr(STDIN_FILENO, TCSANOW, &m_old_settings);
        }

        TerminalRawMode(const TerminalRawMode&) = delete;
        TerminalRawMode& operator=(const TerminalRawMode&) = delete;
    };

    inline bool read_with_timeout(char& character, int timeout_deciseconds)
    {
        termios current_settings{};

        if (tcgetattr(STDIN_FILENO, &current_settings) != 0)
            return false;

        const cc_t old_vmin{current_settings.c_cc[VMIN]};
        const cc_t old_vtime{current_settings.c_cc[VTIME]};

        current_settings.c_cc[VMIN] = 0;
        current_settings.c_cc[VTIME] =
            static_cast<cc_t>(timeout_deciseconds);

        if (tcsetattr(STDIN_FILENO, TCSANOW, &current_settings) != 0)
            return false;

        const ssize_t bytes_read{
            read(STDIN_FILENO, &character, 1)
        };

        current_settings.c_cc[VMIN] = old_vmin;
        current_settings.c_cc[VTIME] = old_vtime;

        tcsetattr(STDIN_FILENO, TCSANOW, &current_settings);

        return bytes_read == 1;
    }

    inline Key getkey()
    {
        TerminalRawMode raw_mode{};

        char first_key{};

        if (read(STDIN_FILENO, &first_key, 1) != 1)
            return Key::Unknown;

        if (first_key == '\n' || first_key == '\r')
            return Key::Enter;

        if (first_key != '\033')
            return Key::Unknown;

        /*
         * Escape alone sends:
         *     ESC
         *
         * Arrow keys send:
         *     ESC [ A    Up
         *     ESC [ B    Down
         *
         * We briefly wait for another byte to distinguish Escape
         * from the beginning of an arrow-key sequence.
         */
        char second_key{};

        if (!read_with_timeout(second_key, 1))
            return Key::Escape;

        if (second_key != '[')
            return Key::Unknown;

        char third_key{};

        if (!read_with_timeout(third_key, 1))
            return Key::Unknown;

        switch (third_key)
        {
            case 'A':
                return Key::Up;

            case 'B':
                return Key::Down;

            default:
                return Key::Unknown;
        }
    }
#endif
}