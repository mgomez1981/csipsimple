package org.cryptocall;

/**
 * Performante and thread-safe impl of singelton
 * 
 * This is a workaround to always get the current session from PjSipService
 */
public class CurrentSessionSingelton {
    private static CurrentSessionSingelton instance = new CurrentSessionSingelton();

    /**
     * Not usable
     */
    private CurrentSessionSingelton() {
    }

    /**
     * get the instance
     */
    public static CurrentSessionSingelton getInstance() {
        return instance;
    }

    private CryptoCallSession cryptoCallSession;

    public CryptoCallSession getCryptoCallSession() {
        return cryptoCallSession;
    }

    public void setCryptoCallSession(CryptoCallSession cryptoCallSession) {
        this.cryptoCallSession = cryptoCallSession;
    }

}
