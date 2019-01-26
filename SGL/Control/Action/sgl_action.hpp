#ifndef sge_action_h
#define sge_action_h

#ifdef _WIN32
	#ifdef SHARED
		#include <control_export.h>
	#else
		#define CONTROL_EXPORT
	#endif
#else
	#define CONTROL_EXPORT
#endif


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
