package org.cryptocall.api;

import android.os.Parcel;
import android.os.Parcelable;

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

    /**
     * 
     * This field is needed for Android to be able to create new objects, individually or as arrays.
     * 
     * This also means that you can use use the default constructor to create the object and use
     * another method to hyrdate it as necessary.
     * 
     * I just find it easier to use the constructor. It makes sense for the way my brain thinks ;-)
     * 
     */
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
        // TODO Auto-generated method stub
        return 0;
    }
}
