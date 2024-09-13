#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <atomic>
#include <conio.h>
#include <iomanip>
#include <vector>
#include <numeric>
#include <cmath>

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
            char c;
            std::vector<int> storekb_before, storekb_after;
            while (!_endOp)
            {
                storekb_before.push_back(kbhit());
                if (kbhit() != 0)
                {
                    c = getch();
                    _keyStart = true;
                }
                storekb_before.push_back(kbhit());
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

    // key_a.init();
    char a, b;
    std::cout << "initializing the vector.\n";
    std::vector<int> heldRegister(10, 0);
    int held_threshold = 0.2 * heldRegister.size();
    bool holding = false;
    std::cout << "outside loop.\n";

    auto start_time = std::chrono::high_resolution_clock::now();
    while (true)
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time);

        // int beforeSum, afterSum = 0;
        int hit = _kbhit();

        int hold_count = 0;
        while (_kbhit())
        {

            for (int i = 1; i < heldRegister.size(); ++i)
            {
                heldRegister[i - 1] = heldRegister[i];
                // std::cout << heldRegister[i - 1] << " ";
            }

            heldRegister.back() = _kbhit() ? 1 : 0;

            hold_count++;
            // clear register
            a = _getch();
        }
        // std::cout << "Left shift register.\n";

        // hold_count = std::accumulate(heldRegister.begin(), heldRegister.end(), 0);

        if (elapsed.count() > 100)
        {
            // std::cout << "kbhit - " << hit << std::endl;
            std::cout << "hold count - " << hold_count << std::endl;
            start_time = std::chrono::high_resolution_clock::now();
            // std::cout << "register size - " << hold_count << "\n";
            // for (int i = heldRegister.size() - 1; i > heldRegister.size() - held_threshold; --i)
            // {
            //     std::cout << heldRegister[i] << " ";
            // }
            // if (hold_count > 0)
            //     std::cout << "\n";
        }

        // std::cout << "check threshold.\n";
        if (hold_count >= held_threshold)
        {
            holding = true;
            std::cout << "holding.\n";
        }
        else
        {
            holding = false;
        }

        // for (int i = 0; i < heldRegister.size(); ++i)
        // {
        //     heldRegister[i] = 0;
        //     // std::cout << heldRegister[i - 1] << " ";
        // }
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
        // if (_kbhit())
        // {
        //     // std::cout << "hit - " << hit << std::endl;
        //     // std::cout << "before size: " << storekb_before.size() << std::endl;
        //     // std::cout << "after size: " << storekb_after.size() << std::endl;
        //     a = _getch();
        //     // std::cout << "collected character\n";
        //     // _keyStart = true;
        // }
    }

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
    //     // std::cout << "hit - " << kbhit() << std::endl;
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
    //         std::cout << "hit - " << kbhit() << std::endl;
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