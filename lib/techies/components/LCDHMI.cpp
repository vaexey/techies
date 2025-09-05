#include "LCDHMI.hpp"
#include "core/event/Manager.hpp"
#define TAG "LCDHMI"

#ifdef TCFG_C_LCDHMI
namespace techies::components
{
    LiquidCrystal LCDHMI::lcd(TCFG_C_LCDHMI_PINS);

    LCDHMI_Printer LCDHMI::printer;
    void LCDHMI::DefaultPrinter(LCDHMI_Display* lcd)
    {
        lcd->setCursor(0,0);
        lcd->print("    techies     ");
        lcd->setCursor(0, 1);
        lcd->print("     LCDHMI     ");
    }

    bool LCDHMI::active = false;
    bool LCDHMI::Active()
    {
        return active;
    }

    void LCDHMI::Init()
    {
        L->Crit(TAG, "Initializing LCD...");
        lcd.begin(TCFG_C_LCDHMI_DIMENSIONS);
        
        printer = &DefaultPrinter;
        printer(&lcd);

        pinMode(TCFG_C_LCDHMI_ABUTTON, INPUT);

        techies::core::event::Manager::AfterCycle
            .Connect(OnAfterCycle);

        active = true;
    }

    LCDHMI_Button MapValueToButton(int val)
    {
        #define COND(btn) (\
            ((val) >= (btn - TCFG_C_LCDHMI_ABUTTON_TOLERANCE)) && \
            ((val) <= (btn + TCFG_C_LCDHMI_ABUTTON_TOLERANCE)) \
        )

        if(COND(TCFG_C_LCDHMI_ABUTTON_SEL))
            return LCDHMI_Button::SEL;
        if(COND(TCFG_C_LCDHMI_ABUTTON_LEFT))
            return LCDHMI_Button::LEFT;
        if(COND(TCFG_C_LCDHMI_ABUTTON_UP))
            return LCDHMI_Button::UP;
        if(COND(TCFG_C_LCDHMI_ABUTTON_DOWN))
            return LCDHMI_Button::DOWN;
        if(COND(TCFG_C_LCDHMI_ABUTTON_RIGHT))
            return LCDHMI_Button::RIGHT;
        
        return LCDHMI_Button::NONE;

        #undef COND
    };

    void LCDHMI::OnAfterCycle()
    {
        auto bval = analogRead(TCFG_C_LCDHMI_ABUTTON);
        auto btn = MapValueToButton(bval);

        printer(&lcd);
    }

    void LCDHMI::SetPrinter(LCDHMI_Printer p)
    {
        printer = p;
    }

} // namespace techies::components
#endif