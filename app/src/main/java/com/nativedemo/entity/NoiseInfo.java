package com.nativedemo.entity;

/**
 * Created by zd on 2017/8/14.
 */

public class NoiseInfo {
    private short eNoiseType;
    private byte cNoiseIntensity;

    public short geteNoiseType() {
        return eNoiseType;
    }

    public void seteNoiseType(short eNoiseType) {
        this.eNoiseType = eNoiseType;
    }

    public byte getcNoiseIntensity() {
        return cNoiseIntensity;
    }

    public void setcNoiseIntensity(byte cNoiseIntensity) {
        this.cNoiseIntensity = cNoiseIntensity;
    }

    @Override
    public String toString() {
        return "NoiseInfo{" +
                "eNoiseType=" + eNoiseType +
                ", cNoiseIntensity=" + cNoiseIntensity +
                '}';
    }
}
