/*
 * Copyright (C) 2011-2013 Sergej Dechand <cryptocall@serj.de>
 *                         Dominik Schürmann <dominik@dominikschuermann.de>
 * 
 * This file is part of CryptoCall.
 * 
 * CryptoCall is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CryptoCall is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CryptoCall.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

package org.cryptocall;

import android.os.Parcel;
import android.os.Parcelable;

/**
 * This contains all necessary information for a CryptoCall session between two participants. It is
 * contained in csipsimple library project to be referenced by CryptoCall and csipsimple.
 */
public class CryptoCallSession implements Parcelable {
    public String peerEmail;
    public String peerName;
    public String peerTelephoneNumber;

    public String serverIp;
    public int serverPort;

    public int peerPublicKeyType;
    public String peerPublicKeyHex;

    public String myX509CertFile;
    public String myX509PrivKeyFile;

    // OpenSSL Keytype choices
    public static final int KEY_TYPE_RSA = 6;
    public static final int KEY_TYPE_DSA = 116;

    public CryptoCallSession() {
    }

    public CryptoCallSession(Parcel in) {
        peerEmail = in.readString();
        peerName = in.readString();
        peerTelephoneNumber = in.readString();
        serverIp = in.readString();
        serverPort = in.readInt();
        peerPublicKeyType = in.readInt();
        peerPublicKeyHex = in.readString();
        myX509CertFile = in.readString();
        myX509PrivKeyFile = in.readString();
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(peerEmail);
        dest.writeString(peerName);
        dest.writeString(peerTelephoneNumber);
        dest.writeString(serverIp);
        dest.writeInt(serverPort);
        dest.writeInt(peerPublicKeyType);
        dest.writeString(peerPublicKeyHex);
        dest.writeString(myX509CertFile);
        dest.writeString(myX509PrivKeyFile);
    }

    @SuppressWarnings("rawtypes")
    public static final Parcelable.Creator CREATOR = new Parcelable.Creator() {
        public CryptoCallSession createFromParcel(Parcel in) {
            return new CryptoCallSession(in);
        }

        public CryptoCallSession[] newArray(int size) {
            return new CryptoCallSession[size];
        }
    };

    @Override
    public int describeContents() {
        // Not needed...
        return 0;
    }

    @Override
    public String toString() {
        String output = "CryptoCall session:\n";
        output += "peerEmail: " + peerEmail + "\n";
        output += "peerName: " + peerName + "\n";
        output += "peerTelephoneNumber: " + peerTelephoneNumber + "\n";
        output += "serverIp: " + serverIp + "\n";
        output += "serverPort: " + serverPort + "\n";
        output += "peerPublicKeyType: " + peerPublicKeyType + "\n";
        output += "peerPublicKeyHex: " + peerPublicKeyHex + "\n";
        output += "myX509CertFile: " + myX509CertFile + "\n";
        output += "myX509PrivKeyFile: " + myX509PrivKeyFile;

        return output;
    }
}
