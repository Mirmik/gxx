#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gxx/event/delegate.h>
#include <gxx/event/once_delegate.h>

class TurtleBase {
public:
	virtual void mtd() = 0;
};

class Turtle : public TurtleBase {
public:
	MOCK_METHOD0(mtd, void());
};

TEST(Event, delegate) {
	Turtle turtle;
	EXPECT_CALL(turtle, mtd()).Times(2);
	gxx::delegate<void> dlg(&Turtle::mtd, &turtle);
	gxx::once_delegate<void> odlg = dlg;

	dlg();
	odlg();
}