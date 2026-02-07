#include "action.hh"
#include "event.hh"

MyActionInitialization::MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::Build() const
{
    MyPrimaryGeneratorAction* generatorAction = new MyPrimaryGeneratorAction();
    SetUserAction(generatorAction);

    MyRunAction* runAction = new MyRunAction();
    SetUserAction(runAction);

    MyEventAction* eventAction = new MyEventAction(runAction);
    SetUserAction(eventAction);
}

void MyActionInitialization::BuildForMaster() const
{
    MyRunAction* runAction = new MyRunAction();
    SetUserAction(runAction);
}
