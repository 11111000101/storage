#include "imainwindowpresenter.hpp"


IMainWindowPresenter::IMainWindowPresenter(IMainWindowView* view, DataModel& model)
    : m_model(model), m_view(view)
{}
