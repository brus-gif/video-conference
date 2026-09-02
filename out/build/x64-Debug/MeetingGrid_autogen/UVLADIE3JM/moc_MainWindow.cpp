/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/MainWindow.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "addMember",
        "",
        "removeMember",
        "onCountSliderChanged",
        "value",
        "onTileClicked",
        "index",
        "onEndCall",
        "onMicToggle",
        "on",
        "onCamToggle",
        "onShareToggle",
        "onViewToggle",
        "onChatToggle",
        "onSendChat",
        "updateTimer",
        "openSettings",
        "onSelfSpeakingChanged",
        "speaking",
        "onWindowMinimize",
        "onWindowMaximizeRestore",
        "onWindowClose",
        "onNetworkClicked",
        "onNetConnected",
        "onNetDisconnected",
        "onNetError",
        "code",
        "message",
        "onRoomCreated",
        "roomId",
        "onJoined",
        "selfId",
        "QList<SignalingClient::Member>",
        "members",
        "onMemberJoined",
        "SignalingClient::Member",
        "member",
        "onMemberLeft",
        "memberId",
        "onMemberUpdated",
        "mic",
        "cam",
        "sharing",
        "onChatMessage",
        "name",
        "text",
        "onRoomClosed",
        "onSelfFrameForNetwork",
        "QImage",
        "frame",
        "onSelfAudioData",
        "pcm",
        "onMediaFrame",
        "kind",
        "senderId",
        "payload",
        "QJsonObject",
        "meta",
        "grabAndSendScreen"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'addMember'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'removeMember'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCountSliderChanged'
        QtMocHelpers::SlotData<void(int)>(4, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 5 },
        }}),
        // Slot 'onTileClicked'
        QtMocHelpers::SlotData<void(int)>(6, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 7 },
        }}),
        // Slot 'onEndCall'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onMicToggle'
        QtMocHelpers::SlotData<void(bool)>(9, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 10 },
        }}),
        // Slot 'onCamToggle'
        QtMocHelpers::SlotData<void(bool)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 10 },
        }}),
        // Slot 'onShareToggle'
        QtMocHelpers::SlotData<void(bool)>(12, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 10 },
        }}),
        // Slot 'onViewToggle'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onChatToggle'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSendChat'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateTimer'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'openSettings'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSelfSpeakingChanged'
        QtMocHelpers::SlotData<void(bool)>(18, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 19 },
        }}),
        // Slot 'onWindowMinimize'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onWindowMaximizeRestore'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onWindowClose'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onNetworkClicked'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onNetConnected'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onNetDisconnected'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onNetError'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(26, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 27 }, { QMetaType::QString, 28 },
        }}),
        // Slot 'onRoomCreated'
        QtMocHelpers::SlotData<void(const QString &)>(29, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 30 },
        }}),
        // Slot 'onJoined'
        QtMocHelpers::SlotData<void(const QString &, const QString &, const QVector<SignalingClient::Member> &)>(31, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 30 }, { QMetaType::QString, 32 }, { 0x80000000 | 33, 34 },
        }}),
        // Slot 'onMemberJoined'
        QtMocHelpers::SlotData<void(const SignalingClient::Member &)>(35, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 36, 37 },
        }}),
        // Slot 'onMemberLeft'
        QtMocHelpers::SlotData<void(const QString &)>(38, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 39 },
        }}),
        // Slot 'onMemberUpdated'
        QtMocHelpers::SlotData<void(const QString &, bool, bool, bool)>(40, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 39 }, { QMetaType::Bool, 41 }, { QMetaType::Bool, 42 }, { QMetaType::Bool, 43 },
        }}),
        // Slot 'onChatMessage'
        QtMocHelpers::SlotData<void(const QString &, const QString &, const QString &)>(44, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 39 }, { QMetaType::QString, 45 }, { QMetaType::QString, 46 },
        }}),
        // Slot 'onRoomClosed'
        QtMocHelpers::SlotData<void()>(47, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSelfFrameForNetwork'
        QtMocHelpers::SlotData<void(const QImage &)>(48, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 49, 50 },
        }}),
        // Slot 'onSelfAudioData'
        QtMocHelpers::SlotData<void(const QByteArray &)>(51, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QByteArray, 52 },
        }}),
        // Slot 'onMediaFrame'
        QtMocHelpers::SlotData<void(const QString &, const QString &, const QByteArray &, const QJsonObject &)>(53, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 54 }, { QMetaType::QString, 55 }, { QMetaType::QByteArray, 56 }, { 0x80000000 | 57, 58 },
        }}),
        // Slot 'grabAndSendScreen'
        QtMocHelpers::SlotData<void()>(59, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->addMember(); break;
        case 1: _t->removeMember(); break;
        case 2: _t->onCountSliderChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->onTileClicked((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->onEndCall(); break;
        case 5: _t->onMicToggle((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->onCamToggle((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->onShareToggle((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 8: _t->onViewToggle(); break;
        case 9: _t->onChatToggle(); break;
        case 10: _t->onSendChat(); break;
        case 11: _t->updateTimer(); break;
        case 12: _t->openSettings(); break;
        case 13: _t->onSelfSpeakingChanged((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 14: _t->onWindowMinimize(); break;
        case 15: _t->onWindowMaximizeRestore(); break;
        case 16: _t->onWindowClose(); break;
        case 17: _t->onNetworkClicked(); break;
        case 18: _t->onNetConnected(); break;
        case 19: _t->onNetDisconnected(); break;
        case 20: _t->onNetError((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 21: _t->onRoomCreated((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 22: _t->onJoined((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QList<SignalingClient::Member>>>(_a[3]))); break;
        case 23: _t->onMemberJoined((*reinterpret_cast<std::add_pointer_t<SignalingClient::Member>>(_a[1]))); break;
        case 24: _t->onMemberLeft((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 25: _t->onMemberUpdated((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[4]))); break;
        case 26: _t->onChatMessage((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3]))); break;
        case 27: _t->onRoomClosed(); break;
        case 28: _t->onSelfFrameForNetwork((*reinterpret_cast<std::add_pointer_t<QImage>>(_a[1]))); break;
        case 29: _t->onSelfAudioData((*reinterpret_cast<std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 30: _t->onMediaFrame((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QByteArray>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QJsonObject>>(_a[4]))); break;
        case 31: _t->grabAndSendScreen(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 22:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 2:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<SignalingClient::Member> >(); break;
            }
            break;
        case 23:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< SignalingClient::Member >(); break;
            }
            break;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    }
    return _id;
}
QT_WARNING_POP
