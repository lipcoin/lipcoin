// Copyright (c) 2009-2016 The LipCoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LIPCOIN_QT_TEST_COMPATTESTS_H
#define LIPCOIN_QT_TEST_COMPATTESTS_H

#include <QObject>
#include <QTest>

class CompatTests : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void bswapTests();
};

#endif // LIPCOIN_QT_TEST_COMPATTESTS_H
