#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <atomic>
#include <conio.h>
#include <iomanip>
#include <vector>

namespace Keyboard
{

    enum KEYBOARD_TYPES
    {
        REGULAR,
        MECHANICAL
    };

    struct TIME_FORMATS
    {
        typedef std::chrono::microseconds microseconds;
        typedef std::chrono::milliseconds milliseconds;
        typedef std::chrono::seconds seconds;
    };

    struct KeyInfo
    {
    private:
        int _keyCode;
        std::string _character;

    public:
        // Operators overload
        KeyInfo &operator=(const std::pair<int, std::string> &other)
        {
            _keyCode = other.first;
            _character = other.second;

            return *this;
        }
        KeyInfo &operator=(const KeyInfo &other)
        {
            _keyCode = other._keyCode;
            _character = other._character;

            return *this;
        }

        // Getters
        int getKeyCode()
        {
            return _keyCode;
        }

        std::string getCharacter()
        {
            return _character;
        }

        // Setters
        void setKeyCode(int keycode)
        {
            _keyCode = keycode;
        }

        void setCharacter(std::string character)
        {
            _character = character;
        }
    };

    struct KeyboardInfo
    {
        std::string _name;
        double _price;
        KEYBOARD_TYPES _type;

        std::string getName()
        {
            return _name;
        }

        double getPrice()
        {
            return _price;
        }

        std::string getType()
        {
            switch (_type)
            {
            case KEYBOARD_TYPES::MECHANICAL:
                return "MECHANICAL";
            case KEYBOARD_TYPES::REGULAR:
                return "REGULAR";
            default:
                return "NULL";
            }
        }
    };

    template <typename K>
    class State
    {
    public:
        State()
        {
            _pressed = _released = _endOp = false;
        }

        // functional methods
        void keyMechanics()
        {
            while (!_endOp)
            {
                char c;
                if (kbhit() != 0)
                {
                    c = getch();
                    _keyStart = true;
                }
            }
        }

        void pressKey(K &k)
        {
            char c;

            while (!_endOp)
            {
                // Checks for if a key is pressed
                // Wait here if no key is pressed
                while (kbhit() == 0)
                    ;

                // if (kbhit() != 0)
                // {
                c = getch();
                k.setCharacter(std::string(1, c));
                k.setKeyCode((int)c);

                _k = k.getKeyCode();
                _pressed = true;
                _released = false;
                std::cout << "key pressed\n";
                // }

                // Wait here if the key hasn't released
                std::cout << "holding key\n";
                while (kbhit() != 0 && _pressed)
                    ;

                std::this_thread::sleep_for(std::chrono::milliseconds(1));

                // Checking if the key pressed is now released
                // if (kbhit() == 0 && _pressed)
                // {
                _released = true;
                _pressed = false;
                _k = k.getKeyCode();

                std::cout << "key released\n";
                // }

                // Checks for if the ESCAPE key was pressed
                if ((int)c == 27)
                    _endOp = true;

                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }

        bool isReleased()
        {
            return _released;
        }

        bool isPressed()
        {
            return _pressed;
        }

        bool isEnd()
        {
            return _endOp;
        }

    private:
        char _k;
        std::atomic_bool _pressed;
        std::atomic_bool _released;
        std::atomic_bool _keyStart;
        std::atomic_bool _endOp;
    };

    template <typename Kb, typename K>
    class Keys
    {
    public:
        // Default Constructors
        Keys()
        {
            _key = {13, "ENTER"};
            _keyboardInfo = {"ALIEN", 99.0, KEYBOARD_TYPES::MECHANICAL};
            _holdTime = 0;
        }

        Keys(Kb kb, K k)
        {
            _key = k;
            _keyboardInfo = kb;
            _holdTime = 0;
        }

        // Setters
        void setKey(K k)
        {
            _key = k;
        }

        // Getters
        K getKey();
        Kb getKeyBoardInfo();

        // Useful method
        bool keyPressed()
        {
            return _state.isPressed();
        }
        bool keyPresedDown()
        {
            return _state.isPressed() && !_state.isReleased();
        }
        // void keyRelease();
        bool keyReleased()
        {
            return _state.isReleased();
        }

        template <typename TF>
        void keyPressedTime()
        {
            while (!_state.isEnd())
            {
                while (!keyPressed())
                    ;

                auto start_time = std::chrono::high_resolution_clock::now();

                while (keyPresedDown())
                    ;

                auto end_time = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<TF>(end_time - start_time);

                _holdTime = duration.count();
            }
        }

        void print()
        {
            while (!_state.isEnd())
            {
                // std::cout << "Key pressed - " << keyPressed()  << "\n";
                // std::cout << "Key held and not released - " << (!keyReleased() && keyPressed())  << "\n";
                // if (keyPresedDown())
                // {
                //     std::cout << "---- PRINTING ----\n"
                //               << "---- Keyboard Information ----"
                //               << std::setw(40)
                //               << "---- Key Information ----\n"
                //               << "Name:\t" << _keyboardInfo.getName()
                //               << std::setw(24)
                //               << "|"
                //               << std::setw(17)
                //               << "Key code: " << _key.getKeyCode()
                //               << std::setw(24)
                //               << "Hold Time: " << _holdTime
                //               << "\nType:\t" << _keyboardInfo.getType()
                //               << std::setw(19)
                //               << "|"
                //               << std::setw(22)
                //               << "Key character: " << _key.getCharacter()
                //               << "\nPrice:\t" << _keyboardInfo.getPrice()

                //               << "\n";
                // }
                // std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }

        void init()
        {
            std::thread stateThread(&State<K>::pressKey, &_state, std::ref(_key));
            std::thread printThread(&print, this);
            std::thread keyPressedTimeThread(&keyPressedTime<TIME_FORMATS::milliseconds>, this);

            stateThread.join();
            printThread.join();
            keyPressedTimeThread.join();
        }

    private:
        Kb _keyboardInfo;
        K _key;
        State<K> _state;
        int64_t _holdTime;
    };
}

int main()
{
    Keyboard::Keys<Keyboard::KeyboardInfo, Keyboard::KeyInfo> key_a;

    key_a.init();
    // char a, b;
    // std::vector<char> storeHeld;

    // while (true)
    // {
    //     // std::cout << "waiting for key press\n";
    //     // while (kbhit() == 0)
    //     //     ;
    //     // char c = getch();
    //     // std::cout << "pressed\n";
    //     // while (kbhit() != 0 && c == getch())
    //     //     std::cout << "holding\n";

    //     // std::cout << "released\n";
    //     bool pressed, holding, released = false;
    //     if (kbhit() != 0)
    //     {
    //         std::cout << "hit - " << kbhit() << std::endl;
    //         a = getch();

    //         // pressed = true;

    //         // storeHeld.push_back(a);

    //         // if (storeHeld[storeHeld.size() - 1] == storeHeld[0] && pressed)
    //         // {
    //         //     std::cout << "holding" << std::endl;
    //         //     holding = true;
    //         //     released = false;
    //         // }
    //         // else
    //         // {
    //         //     storeHeld.clear();
    //         //     std::cout << "released" << std::endl;
    //         //     // a = getch();
    //             std::cout << "hit - " << kbhit() << std::endl;
    //         //     released = true;
    //         //     holding = false;
    //         //     pressed = false;
    //         //     // storeHeld.push_back(a);
    //         // }
    //     }
    // }

    // key_a.print();
    return 0;
}