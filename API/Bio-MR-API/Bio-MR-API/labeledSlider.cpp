#include "labeledSlider.h"

#include <QHBoxLayout>
#include <QFont>
#include <QFontMetrics>

LabeledSlider::LabeledSlider(QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f) 
{
	QHBoxLayout* pLayout = new QHBoxLayout(this);


	m_pSlider = new QSlider(Qt::Horizontal, this);
	m_pSlider->setMinimum(0);
	m_pSlider->setMaximum(100);
	connect(m_pSlider, &QSlider::valueChanged, this, &LabeledSlider::OnSliderValueChanged);


	m_pLabel = new QLabel(this);
	QFont font = QFont();
	QFontMetrics fm(font);
	int width = fm.horizontalAdvance("8.88");

	m_pLabel->setMinimumWidth(width);
	OnSliderValueChanged(m_pSlider->minimum());

	// Setup the layout
	pLayout->addWidget(m_pLabel);
	pLayout->addWidget(m_pSlider);
	setLayout(pLayout);
}

double LabeledSlider::GetDoubleValue()
{
	double percentile = (double)m_pSlider->value() / ((double)m_pSlider->maximum() - (double)m_pSlider->minimum());
	double actualValue = minValue + (percentile) * (maxValue - minValue);
	return actualValue;
}

void LabeledSlider::OnSliderValueChanged(int /*value*/)
{
	double doubleValue = GetDoubleValue();

	int decimals = 0;
	if (doubleValue < 10) {
		decimals = 1;
	}
	if (doubleValue < 1) {
		decimals = 2;
	}

	QString newLabel = QString("%1").arg(doubleValue, 0, 'f', decimals);
	m_pLabel->setText(newLabel);

	emit valueChanged(doubleValue);
}