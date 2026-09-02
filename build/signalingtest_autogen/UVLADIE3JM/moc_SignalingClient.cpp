/****************************************************************************
** Meta object code from reading C++ file 'SignalingClient.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/SignalingClient.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SignalingClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.3. It"
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
struct qt_meta_tag_ZN15SignalingClientE_t {};
} // unnamed namespace

template <> constexpr inline auto SignalingClient::qt_create_metaobjectdata<qt_meta_tag_ZN15SignalingClientE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SignalingClient",
        "connected",
        "",
        "disconnected",
        "roomCreated",
        "roomId",
        "joined",
        "selfId",
        "QList<SignalingClient::Member>",
        "members",
        "memberJoined",
        "SignalingClient::Member",
        "member",
        "memberLeft",
        "memberId",
        "memberUpdated",
        "mic",
        "cam",
        "sharing",
        "chatMessage",
        "name",
        "text",
        "roomClosed",
        "errorOccurred",
        "code",
        "message",
        "pong",
        "mediaFrameReceived",
        "kind",
        "senderId",
        "payload",
        "QJsonObject",
        "meta"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'connected'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'disconnected'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'roomCreated'
        QtMocHelpers::SignalData<void(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Signal 'joined'
        QtMocHelpers::SignalData<void(const QString &, const QString &, const QVector<SignalingClient::Member> &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 }, { QMetaType::QString, 7 }, { 0x80000000 | 8, 9 },
        }}),
        // Signal 'memberJoined'
        QtMocHelpers::SignalData<void(const SignalingClient::Member &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 12 },
        }}),
        // Signal 'memberLeft'
        QtMocHelpers::SignalData<void(const QString &)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 14 },
        }}),
        // Signal 'memberUpdated'
        QtMocHelpers::SignalData<void(const QString &, bool, bool, bool)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 14 }, { QMetaType::Bool, 16 }, { QMetaType::Bool, 17 }, { QMetaType::Bool, 18 },
        }}),
        // Signal 'chatMessage'
        QtMocHelpers::SignalData<void(const QString &, const QString &, const QString &)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 14 }, { QMetaType::QString, 20 }, { QMetaType::QString, 21 },
        }}),
        // Signal 'roomClosed'
        QtMocHelpers::SignalData<void()>(22, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'errorOccurred'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 24 }, { QMetaType::QString, 25 },
        }}),
        // Signal 'pong'
        QtMocHelpers::SignalData<void()>(26, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'mediaFrameReceived'
        QtMocHelpers::SignalData<void(const QString &, const QString &, const QByteArray &, const QJsonObject &)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 28 }, { QMetaType::QString, 29 }, { QMetaType::QByteArray, 30 }, { 0x80000000 | 31, 32 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<SignalingClient, qt_meta_tag_ZN15SignalingClientE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SignalingClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15SignalingClientE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15SignalingClientE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15SignalingClientE_t>.metaTypes,
    nullptr
} };

void SignalingClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SignalingClient *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->roomCreated((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->joined((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QList<SignalingClient::Member>>>(_a[3]))); break;
        case 4: _t->memberJoined((*reinterpret_cast<std::add_pointer_t<SignalingClient::Member>>(_a[1]))); break;
        case 5: _t->memberLeft((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->memberUpdated((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[4]))); break;
        case 7: _t->chatMessage((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3]))); break;
        case 8: _t->roomClosed(); break;
        case 9: _t->errorOccurred((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 10: _t->pong(); break;
        case 11: _t->mediaFrameReceived((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QByteArray>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QJsonObject>>(_a[4]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 2:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<SignalingClient::Member> >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< SignalingClient::Member >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (SignalingClient::*)()>(_a, &SignalingClient::connected, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (SignalingClient::*)()>(_a, &SignalingClient::disconnected, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (SignalingClient::*)(const QString & )>(_a, &SignalingClient::roomCreated, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (SignalingClient::*)(const QString & , const QString & , const QVector<SignalingClient::Member> & )>(_a, &SignalingClient::joined, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (SignalingClient::*)(const SignalingClient::Member & )>(_a, &SignalingClient::memberJoined, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (SignalingClient::*)(const QString & )>(_a, &SignalingClient::memberLeft, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (SignalingClient::*)(const QString & , bool , bool , bool )>(_a, &SignalingClient::memberUpdated, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (SignalingClient::*)(const QString & , const QString & , const QString & )>(_a, &SignalingClient::chatMessage, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (SignalingClient::*)()>(_a, &SignalingClient::roomClosed, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (SignalingClient::*)(const QString & , const QString & )>(_a, &SignalingClient::errorOccurred, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (SignalingClient::*)()>(_a, &SignalingClient::pong, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (SignalingClient::*)(const QString & , const QString & , const QByteArray & , const QJsonObject & )>(_a, &SignalingClient::mediaFrameReceived, 11))
            return;
    }
}

const QMetaObject *SignalingClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SignalingClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15SignalingClientE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SignalingClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void SignalingClient::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SignalingClient::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SignalingClient::roomCreated(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void SignalingClient::joined(const QString & _t1, const QString & _t2, const QVector<SignalingClient::Member> & _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2, _t3);
}

// SIGNAL 4
void SignalingClient::memberJoined(const SignalingClient::Member & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void SignalingClient::memberLeft(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void SignalingClient::memberUpdated(const QString & _t1, bool _t2, bool _t3, bool _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2, _t3, _t4);
}

// SIGNAL 7
void SignalingClient::chatMessage(const QString & _t1, const QString & _t2, const QString & _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1, _t2, _t3);
}

// SIGNAL 8
void SignalingClient::roomClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void SignalingClient::errorOccurred(const QString & _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1, _t2);
}

// SIGNAL 10
void SignalingClient::pong()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void SignalingClient::mediaFrameReceived(const QString & _t1, const QString & _t2, const QByteArray & _t3, const QJsonObject & _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 11, nullptr, _t1, _t2, _t3, _t4);
}
QT_WARNING_POP
