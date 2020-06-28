#include <observed_widget.h>

ObservedWidget::ObservedWidget(std::string id) : id_(id) { }

void ObservedWidget::RegisterObserver(MessageWriter *observer) {
	observers_.insert(observer);
	Notify(observer);
}

void ObservedWidget::RemoveObserver(MessageWriter *observer) {
	observers_.erase(observer);
}

void ObservedWidget::Notify(MessageWriter *observer) {
	*observer << id_ << " ";
	PrintValue(*observer);
	observer->Flush();
}

void ObservedWidget::NotifyAll() {
	for (auto observer : observers_) {
		Notify(observer);
	}
}
