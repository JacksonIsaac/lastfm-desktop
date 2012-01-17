
#include <QToolBar>
#include <QToolButton>
#include <QShortcut>

#include "PreferencesDialog.h"
#include "ui_PreferencesDialog.h"

PreferencesDialog::PreferencesDialog( QMenuBar* menuBar, QWidget* parent )
    :unicorn::MainWindow( menuBar, parent ),
    ui( new Ui::PreferencesDialog )
{
    ui->setupUi( this );

    setAttribute( Qt::WA_DeleteOnClose, true );

    static_cast<QAbstractButton*>( ui->toolBar->widgetForAction( ui->actionGeneral ) )->setAutoExclusive( true );
    static_cast<QAbstractButton*>( ui->toolBar->widgetForAction( ui->actionScrobbling ) )->setAutoExclusive( true );
    static_cast<QAbstractButton*>( ui->toolBar->widgetForAction( ui->actionDevices ) )->setAutoExclusive( true );
    static_cast<QAbstractButton*>( ui->toolBar->widgetForAction( ui->actionAccounts ) )->setAutoExclusive( true );
    static_cast<QAbstractButton*>( ui->toolBar->widgetForAction( ui->actionAdvanced ) )->setAutoExclusive( true );

    connect( ui->toolBar->widgetForAction( ui->actionGeneral ), SIGNAL(toggled(bool)), ui->actionGeneral, SLOT(setChecked(bool)) );
    connect( ui->toolBar->widgetForAction( ui->actionScrobbling ), SIGNAL(toggled(bool)), ui->actionScrobbling, SLOT(setChecked(bool)) );
    connect( ui->toolBar->widgetForAction( ui->actionDevices ), SIGNAL(toggled(bool)), ui->actionDevices, SLOT(setChecked(bool)) );
    connect( ui->toolBar->widgetForAction( ui->actionAccounts ), SIGNAL(toggled(bool)), ui->actionAccounts, SLOT(setChecked(bool)) );
    connect( ui->toolBar->widgetForAction( ui->actionAdvanced ), SIGNAL(toggled(bool)), ui->actionAdvanced, SLOT(setChecked(bool)) );

    connect( this, SIGNAL( saveNeeded() ), ui->general, SLOT( saveSettings() ) );
    connect( this, SIGNAL( saveNeeded() ), ui->scrobbling, SLOT( saveSettings() ) );
    connect( this, SIGNAL( saveNeeded() ), ui->ipod, SLOT( saveSettings() ) );
    connect( this, SIGNAL( saveNeeded() ), ui->accounts, SLOT( saveSettings() ) );
    connect( this, SIGNAL( saveNeeded() ), ui->advanced, SLOT( saveSettings() ) );

    connect( ui->general, SIGNAL( settingsChanged() ), SLOT( onSettingsChanged() ) );
    connect( ui->scrobbling, SIGNAL( settingsChanged() ), SLOT( onSettingsChanged() ) );
    connect( ui->ipod, SIGNAL( settingsChanged() ), SLOT( onSettingsChanged() ) );
    connect( ui->accounts, SIGNAL( settingsChanged() ), SLOT( onSettingsChanged() ) );
    connect( ui->advanced, SIGNAL( settingsChanged() ), SLOT( onSettingsChanged() ) );

    connect( ui->actionGeneral, SIGNAL(triggered()), SLOT(onTabButtonClicked()));
    connect( ui->actionScrobbling, SIGNAL(triggered()), SLOT(onTabButtonClicked()));
    connect( ui->actionDevices, SIGNAL(triggered()), SLOT(onTabButtonClicked()));
    connect( ui->actionAccounts, SIGNAL(triggered()), SLOT(onTabButtonClicked()));
    connect( ui->actionAdvanced, SIGNAL(triggered()), SLOT(onTabButtonClicked()));

#ifndef Q_OS_MAC
//    connect( ui.buttons, SIGNAL( accepted() ), this, SLOT( onAccepted() ) );
//    connect( ui.buttons, SIGNAL( rejected() ), this, SLOT( reject() ) );
//    connect( ui.buttons->button( QDialogButtonBox::Apply ), SIGNAL( clicked() ), SLOT( onApplyButtonClicked() ) );
#endif

    ui->actionGeneral->trigger();
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}


void
PreferencesDialog::closeEvent( QCloseEvent* )
{
    emit saveNeeded();
}

void
PreferencesDialog::onTabButtonClicked()
{
    QAction* clickedButton = qobject_cast<QAction*>(sender());

    setWindowTitle( clickedButton->text() );

    if ( clickedButton == ui->actionGeneral )
        ui->stackedWidget->setCurrentWidget( ui->general );
    else if ( clickedButton == ui->actionAccounts )
        ui->stackedWidget->setCurrentWidget( ui->accounts );
    else if ( clickedButton == ui->actionDevices )
        ui->stackedWidget->setCurrentWidget( ui->ipod );
    else if ( clickedButton == ui->actionAdvanced )
        ui->stackedWidget->setCurrentWidget( ui->advanced );
    else if ( clickedButton == ui->actionScrobbling )
        ui->stackedWidget->setCurrentWidget( ui->scrobbling );
}

void
PreferencesDialog::onAccepted()
{
    emit saveNeeded();
    close();
}

void
PreferencesDialog::onSettingsChanged()
{
#ifndef Q_OS_MAC
    //ui->buttons->button( QDialogButtonBox::Apply )->setEnabled( true );
#endif
}

void
PreferencesDialog::onApplyButtonClicked()
{
#ifndef Q_OS_MAC
    emit saveNeeded();
    //ui->buttons->button( QDialogButtonBox::Apply )->setEnabled( false );
#endif
}
