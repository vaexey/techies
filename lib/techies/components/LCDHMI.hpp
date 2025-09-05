#include "core/Config.hpp"
#include <LiquidCrystal.h>

#ifdef TCFG_C_LCDHMI
namespace techies::components
{
    typedef LiquidCrystal LCDHMI_Display;
    typedef void (*LCDHMI_Printer)(LCDHMI_Display*);

    enum class LCDHMI_Button
    {
        NONE,
        SEL,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    struct LCDHMI_Buttons
    {
        bool SEL : 1;
        bool UP : 1;
        bool DOWN : 1;
        bool LEFT : 1;
        bool RIGHT : 1;
    };

    class LCDHMI
    {
    protected:
        static bool active;
        static LCDHMI_Display lcd;

        static LCDHMI_Printer printer;

        static void DefaultPrinter(LCDHMI_Display* lcd);

    public:
        static void Init();
        static bool Active();

        static void OnAfterCycle();

        static void SetPrinter(LCDHMI_Printer printer);
    };
} // namespace techies::components
#endif