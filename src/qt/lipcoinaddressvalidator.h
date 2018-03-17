// Copyright (c) 2011-2014 The LipCoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LIPCOIN_QT_LIPCOINADDRESSVALIDATOR_H
#define LIPCOIN_QT_LIPCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class LipCoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit LipCoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** LipCoin address widget validator, checks for a valid lipcoin address.
 */
class LipCoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit LipCoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // LIPCOIN_QT_LIPCOINADDRESSVALIDATOR_H
