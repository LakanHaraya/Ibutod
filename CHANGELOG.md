# Changelog

## [0.1.3] — Pagkakakilanlan ng Instansiya at Pamamahala ng Ikot-Buhay (*Instance Identity and Lifecycle Control*) 

## [0.1.2] — Estado ng Pagtakbo ng Instansiya (*Instance Runtime State*)
### Idinagdag
- Nagdagdag ng `UbodState` para sa lifecycle ng bawat `UbodCore` instance.
- Nagdagdag ng instance-specific runtime state at start time.
- Ginawang instance-relative ang `uptime()`.
- Nagdagdag ng Serial Monitor test para sa dalawang `UbodCore` instance.
### Sinubukan
- Independent initialization ng `coreA` at `coreB`.
- Magkaibang initialization time at uptime ng bawat instance.
- Paglipat ng bawat instance mula sa `READY` patungong `RUNNING`.
### Tala
- Shared pa rin ang platform clock (`millis()`).
- Eksperimental pa rin ang lifecycle API at maaaring baguhin sa mga susunod na bersiyon.

## [0.1.1] — Eksperimento para sa Maramihang Instansiya (*Multi-Instance Experiment*)
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

## [0.1.0] — Munting Balangkas ng Pagpapatakbo (*Minimal Runtime Skeleton*)
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