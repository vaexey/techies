namespace techies::modules
{
    struct POSEDGE
    {
        bool Q;
        bool memory;

        static void Cycle(const POSEDGE* Old, POSEDGE* New, bool IN);
        static void Reset(POSEDGE* New);
    };

    struct NEGEDGE
    {
        bool Q;
        bool memory;

        static void Cycle(const NEGEDGE* Old, NEGEDGE* New, bool IN);
        static void Reset(NEGEDGE* New);
    };

} // namespace techies::modules
