#ifndef sge_action_h
#define sge_action_h

namespace SGL
{
	class Action
	{
    protected:
        bool active = false;
		Action();
		explicit Action(bool active);

    public:
		bool isActive() const;
		virtual ~Action() = default;
        virtual void perform();
    };
}
#endif /* sge_action_h */
