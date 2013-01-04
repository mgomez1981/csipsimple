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

    public String email;

    public String name;
    public String telephoneNumber;

    public String serverIp;
    public int serverPort;

    public int publicKeyType;
    public String publicKeyHex;

    public String X509CertFile;
    public String X509PrivKeyFile;

    public CryptoCallSession() {
    }

    public CryptoCallSession(Parcel in) {
        email = in.readString();
        name = in.readString();
        telephoneNumber = in.readString();
        serverIp = in.readString();
        serverPort = in.readInt();
        publicKeyType = in.readInt();
        publicKeyHex = in.readString();
        X509CertFile = in.readString();
        X509PrivKeyFile = in.readString();
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(email);
        dest.writeString(name);
        dest.writeString(telephoneNumber);
        dest.writeString(serverIp);
        dest.writeInt(serverPort);
        dest.writeInt(publicKeyType);
        dest.writeString(publicKeyHex);
        dest.writeString(X509CertFile);
        dest.writeString(X509PrivKeyFile);
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
}
