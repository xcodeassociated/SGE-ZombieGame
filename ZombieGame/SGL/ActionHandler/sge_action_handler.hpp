#ifndef SGE_ACTION_HANDLER_HPP
#define SGE_ACTION_HANDLER_HPP

#include <vector>

namespace SGE
{
	enum class LogicPriority;
	class Action;

    struct KeyHash
	{
        template <typename T>
	    std::size_t operator()(T t) const
		{
			return static_cast<std::size_t>(t);
		}
    };

	template <typename Key>
    using KeyHashAlias = typename std::conditional<std::is_enum<Key>::value, KeyHash, std::hash<Key>>::type;

    class ActionHandler
	{
        std::vector<Action*>* actions;

	public:

	    explicit ActionHandler();

	    void performSingleAction(Action* action, LogicPriority priority);

		void setActions(std::vector<Action*>& actionsVec); //TODO: this method has tobe triggered when swapping scene

		void triggerActionSingle(Action* action);

		void addAction(Action* action);

		std::vector<Action*>& getActions();
	};

}

#endif // !SGE_ACTION_HANDLER_HPP
