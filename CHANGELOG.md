# Changelog
## [0.1.7] — Pagkakaroon ng Puwang ng Ubod (*Core Slot Availability*)
### Idinagdag
- Idinagdag ang `UbodAvailabaility` para sa kalagayan ng Core Slot.
- Idinagdag ang `FREE` at `OCCUPIED` na availability states.
- Idinagdag ang `occupy()`, `free()`, `availability()`, `isFree()`, at `isOccupied()`.
### Binago
- Hiniwalay ang availability ng Core Slot sa lifecycle state ng Ubod.
- Ang bagong Core Slot ay nagsisimula bilang `FRRE`.
- Hindi awtomatikong binabago ng `begin()` ang availability.
### Sinubukan
- `FREE` patungong `OCCUPIED` gamit ang `occupy()`.
- Pagtanggi sa paulit-ulit na `occupy()`.
- `OCCUPIED` patungong `FREE` gamit ang `free()`.
- Pagtanggi sa paulit-ulit na `free()`.
- Malayang availability ng magkakaibang Core Slot.
- Pagkakahiwalay ng lifecycle state at availability.
### Tala
- Hindi pa binabago ang kasalukuyang semantika ng `release()`.
- Hindi pa kasama ang Core Engine assignment at Static Core Slot Pool.

## [0.1.6] — Pagpapatibay ng Pangalan ng Ubod (*Core Name Validation*)
### Idinagdag
- Nagdagdag ng validation para sa Core Name.
- Tinatanggihan ang `nullptr`, empty string, at whitespace-only names.
- Nililimitahan ang Core Name sa maximum na 15 character.
- Pinapayagan ang spaces, hyphens, underscores, at numeric names.
- Pinapayagan ang magkaparehong Core Name sa magkakaibang Core Slot.
### Binago
- Ang invalid na bagong pangalan ay hindi nakapagbabago nsa kasalukuyang valid na pangalan.
- Pinananatili ang kasalukuyang Core Name kapag `RELEASED` ang Core.
- Hindi maaaring magpalit ng pangalan ang isang released Core.
### Tala
- Normal naming. 
- Walang empty at whitespace-only names.
- Maximum name length.
- Duplicate names.
- Core renaming.
- Name retention pagkatapos ng `release()`.

## [0.1.5] — Pagpapangalan sa Puwang ng Ubod (*Core Slot Naming*)
### Idinagdag
- Nagdagdag ng human-readable name para sa bawat Core Slot.
- Nagdagdag ng `setName()` at `name()` API.
- Gumamit ng fixed-sized character buffer upang maiwasan ang dynamic memory allocation.
- Nagdagdag ng validation para sa null at sobrang habang pangalan.
### Binago
- Pinananatili ang huling Core Name kapag ang Core ay `RELEASED`.
- Hindi na maaaring baguhin ang pangalan ng isang released Core.
### Tala
- Pinapayagan ang magkaparehong Core Name dahil ang Core ID pa rin ang natatanging identity ng slot.
- Napanatili ang kasalukuyang Core ID at lifecycle behavior.   

## [0.1.4] — Ikot-Buhay ng Instansiya at Pagpapalaya ng Pagkakakilanlan (*Instance Lifecycle and Identity Release*)
### Idinagdag 
- `release()` API para sa `UbodCore`.
- `Released` state para sa mga instance na natapos na ang lifecycle.
- `Invalid` state para sa mga instance na hindi nakakuha ng valid identity.
- Pagpapalaya ng instance ID kapag nag-release.
- Muling paggamit ng dating released na instance ID.
- Pag-freeze ng uptime kapag released na ang instnace.
### Binago
- Hindi na maaaring muling i-activate ang isang released na `UbodCore`.
- Ang duplicate o hindi available na instance ID ay nagreresulta sa `Invalid` state.
- Ang invalid na instance ay nananatiling `Invalid` sa `begin()` at `update()`.
### Sinubukan
- Multiple instances sa loob ng MCU/device scope.
- Duplicate instance ID detection.
- Instance release at identity release.
- Reuse ng released instance ID.
- Pagpigil sa ressurection ng released instance.
- Pagpapanatili ng `Invalid` state ng failed instance.
### Tala
- Ang instance ID ay nananatiling nasa **MCU/device scope**.
- Ang `Released` at `Invalid` ay magkaibang lifecycle conditions.
- Hindi pa bahagi ng bersiyong ito ang dynamic memory allocation, instance pool, o user-assigned instance name.

## [0.1.3] — Pagkakakilanlan ng Instansiya at Pagtukoy ng Magkaparehong ID (*Instance Identity and Duplicate Detection*)
### Idinagdag 
- User-assigned instance ID para sa bawat `UbodCore`.
- Pagpapatunay ng duplicate instance ID.
- `id()` at `isIdValid()` API.
- Paunang instance registry para sa identity validation.
### Sinubukan
- Dalawang valid na instance na may magkakaibang ID.
- Duplicate ID sa dalawang `UbodCore` instance.
- Pagpigil sa initialization ng instance na may duplicate ID.
### Tala
- Ang instance ID ay nakalaan para sa **MCU/device** scope.
- Eksperimental pa ang registry at identity lifecycle.

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