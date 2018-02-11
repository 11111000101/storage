#ifndef IMAINWINDOWPRESENTER_HPP
#define IMAINWINDOWPRESENTER_HPP

class DataModel;
class IMainWindowView;

class IMainWindowPresenter
{
public:
    IMainWindowPresenter(IMainWindowView* view, DataModel& model);
    virtual void setUp() = 0;
    virtual void show() = 0;

protected:
    DataModel& m_model;
    IMainWindowView* m_view;
};

#endif // IMAINWINDOWPRESENTER_HPP
