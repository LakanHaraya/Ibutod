# Changelog

## [0.1.1] — Eksperimento para sa Maramihang Instansiya
### Idinagdag
- Suporta sa paglikha ng maraming instansiya ng `UbodCore`.
- Pangunahing runtime API:
    - `begin()`
    - `update()`
    - `isReady()`
    - `uptime()`
- Paunang eksperimento sa magkakahiwalay na instansiya ng `UbodCore`.
- Demostrasyon sa Serial Monitor para sa dalawang instansiya ng Ubod. 
### Sinubukan
- Dalawang instansiya ng `UbodCore` sa iisang Arduino Nano ESP32.
- Magkahiwalay na pagtawag ng `begin()` at `update()` para sa bawat instansiya.
- Pagbasa ng runtime information sa pamamagitan ng Serial Monitor.

## [0.1.0] — Munting Balangkas ng Pagpapatakbo
### Idinagdag
- Paunang klase ng `UbodCore`.
- Pangunahing lifecycle API:
    - `begin()`
    - `update()`
- Paunang pagsasama ng Ubod sa Arduino `setup()` at `loop()`.
- Paunang library structure sa `lib/Ubod/src/`.
### Sinubukan
- Pagbuo gamit ang PlatformIO
- Pag-upload sa Arduino Nano ESP32
- Pangunahing runtime integration sa Arduino Framework.
### Tala
- Ang bersiyon ito ay nagsilbing panimulang runtime skeleton.
- Hindi pa tinukoy bilang pangwakas ang arkitektura ng Ubod.
