class Action;

class Trigger {

private:
	std::vector<Action> targets;
public:
	std::string id;
	Trigger(std::string ID) {
		id = ID;
	}
	Trigger* register(Action target) {
		targets.push_back(target);
	}
	bool run() {
		// do stuff on actions
		return true;
	}

};

class Action {

public:
	Trigger* trigger;
	Action(&Trigger TR) {
		trigger = TR.register(this);
	}
};

void Example() {
	Trigger order_created("@order.created");
	Action id_2133(order_created);

	order_created.run(); // this should execute actions assigned to trigger, in this scenario id_2133
}
