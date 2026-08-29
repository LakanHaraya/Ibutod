# Changelog
Lahat ng kapansin-pansing pagbabago sa proyektong ito ay idodokumento sa file na ito.

Ang format ay batay sa [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).
Sa kasalukuyang eksperimental na yugto ng **Ubod**, ang mga bersiyon sa seryeng `v0.1.x` ay nagsisilbing sunod-sunod na development versions. Maaaring magkaroon ng breaking changes, pagbabago sa API, o kawalan ng backward compatibility sa pagitan ng mga bersiyon. Ang version numbering sa yugtong ito ay hindi pa mahigpit na sumusunod sa [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.1.12] — Paglilinaw ng Semantika ng Attachment ng Slot (*Slot Attachment Semantics Alignment*)
### Binago 
- Pinalitan ang `occupy()` ng `attach()` bilang pangunahing operasyon para markahan ang isang Slot bilang may nakakabit na Engine.
- Pinalitan ang `free()` ng `detach()` bilang operasyon para alisin ang attachment mula sa isang Slot.
- Pinalitan ang `UbodContainer::occupy(id)` ng `UbodContainer::attach(id)`
- Pinalitan ang `UbodContainer::free(id)` ng `UbodContainer::detach(id)`
- Inalis ang `release()` API mula sa `UbodSlot`.
- Inalis ang `Released` state mula sa `UbodSlotState`.
- Inalis ang `_finalUptime` dahil wala nang Slot release lifecycle sa kasalukuyang modelo.
- Inihanay ang `FREE` at `OCCUPIED` availability sa konsepto ng Engine attachment sa Slot.
### Sinubukan
- Paunang estado ng Slot bilang `FREE`
- Paglipat ng Slot mula `FREE` patungong `OCCUPIED` gamit ang `attach()`.
- Paglipat ng Slot mula `OCCUPIED` patungong `FREE` gamit ang `detach()`.
- Pagtanggi sa paulit-ulit na `attach()` sa isang `OCCUPIED` Slot.
- Pagtanggi sa paulit-ulit na `detach()` sa isang `FREE` Slot.
- Paggamit ng `UbodContainer::attach(id)` at `UbodContainer::detach(id)` bilang conatiner-level operation.
- Pagbilang ng `OCCUPIED` at `FREE` Slots gamit ang `used()` at `findFree()`.
- Pagpapatunay na magkahiwalay ang Slot lifecycle at attachment status.
### Tala
- Ang `attach()` at `detach()` ay kasalukuyang naglalarawan ng attachment state transition ng Slot.
- Sa bersiyong ito, wala pang aktuwal na `Core Engine` object na ipinapasa o iniimbak sa `UbodSlot`.
- Ang `OCCUPIED` ay nangangahulugang may conceptual attachment ang Slot, habang ang `FREE` ay nangangahulugang walang attachment.
- Hindi pa tinutukoy ang Engine identity, Engine ownership, lifetime management, o kongkretong attachment reference.
- Ang Slot lifecycle (`Initializing`, `Ready`, at `Running`) ay nananatiling hiwalay sa attachment status (`FREE` at `OCCUPIED`).
- Ang pagtanggal ng `release()` at `Released` state ay isang breaking API at semantic change.
- Ang memory model ay nananatiling static at bounded, walang dynamic memory allocation.

## [0.1.11] — Pagtutuwid ng Terminolohiya sa Core Slot (*Core Slot Terminology Alignment*)
### Binago 
- Pinalitan ang `UbodCore` ng `UbodSlot` upang malinaw na kumatawan sa Core Slot bilang resource slot.
- Pinalitan ang `UbodState` ng `UbodSlotState`.
- Pinalitan ang `UbodAvailability` ng `UbodSlotAvailability`.
- Pinalitan ang Core ID ng Slot ID.
- Pinalitan ang Core Name ng Slot Name.
- Pinalitan ang `setName()` ng `setSlotName()`.
- Pianlitan ang `name()` ng `slotName()`.
- Pinalitan ang `findByName()` ng `findBySlotName()`.
- Pinalitan ang internal na `_cores` storage ng `_slots`.
- Inihanay ang source code, API, comment, at experiment sa konsepto na ang `UbodSlot` ay hindi Core Engine.
### Sinubukan
- Pagbuo ng test code matapos ang terminology refactor.
- Pag-upload at pagpapatakbo sa Arduino Nano ESP32.
- Paglikha at pagkuha ng `UbodSlot` sa `UbodContainer`.
- Pagpapatunay ng Slot ID at Slot Name.
- Slot lifecycle gamit ang `begin()` at `update()`.
- Slot availability gamit ang `occupy()` at `free()`.
- Paghahanap ng maramihang Slot gamit ang `findBySlotName()`.
- Slot release at pagpigil sa operasyon ng released Slot.
### Tala
- Ang `UbodSlot` ay kumakatawan sa resource slot at hindi sa Core Engine.
- Hindi pa tinutukoy sa bersiyong ito ang Engine identity, Engine ownership, o attachement/detachment model.
- Ang kasalukuyang `release()` ay nananatiling lifecycle operation ng Slot, hindi pa ito itinuturing na Engine `detach()`.
- Ang pagbabago mula sa `UbodCore` patungong `UbodSlot` ay isang breaking terminology/API change.
- Nanatiling static at bounded ang memory model.

## [0.1.10] — Pagtuklas at Paghahanap ng Puwang ng Ubod (*Core Slot Dicovery and Lookup*)
### Idinagdag
- Idinagdag ang `findByName()` para sa paghahanap ng Core Slots batay sa Core Name.
- Sinusuportahan ang maramihang Core Slots na may magkakaparehong pangalan.
- Gumagamit ng caller-owned fixed result buffer para sa mga resulta.
- Nililimitahan ang bilang ng resulta ayon sa `maxResults`.
- Nanatiling static at bounded ang memory; walang dynamic memory allocation.
### Sinubukan 
- Paghahanap ng dalawang Core Slots na may parehong pangalan.
- Paghahanap na may `maxResults = 1`.
- Paghahanap ng pangalang walang katugma.
- `nullptr` na pangalan.
- `nullptr` na result buffer.
- `maxResults = 0`.
### Tala
- Ang Core Name ay hindi kailangang unique sa loob ng `UbodContainer`.
- Ang mga resulta ay ibinibigay sa caller-owned buffer; hindi nag-allocate ng result sa memory ang Ubod.
- Ang mga resulta ay ibinabalik ayon sa pagkakasunod ng Core Slot ID.
- Hindi muna idinagdag ang `findAllByName()` API.


## [0.1.9] — API ng Operasyon sa Puwang ng Ubod (*Core Slot Operation API*)
### Idinagdag 
- Idinagdag ang `UbodContainer::occupy(id)` para sa ligtas na pag-okupa ng Core Slot.
- Idinagdag ang `UbodContainer::free(id)` para sa pagpapalaya ng Core Slot.
- Ginawang gatekeeper ang `UbodContainer` para sa mga operasyon sa Core Slot.
- Idinagdag ang proteksiyon laban sa invalid o lampas-sa-kapasidad na Core Slot ID.
### Binago
- Inirerekomenda ang paggamit ng `UbodContainer` operation API sa halip na direktang pagmamanipula ng `UbodCore`.
- Pinanatili ang static memory allocation at compile-time Core Slot capacity.
### Sinubukan
- Sinubukan ang matagumpay na pag-okupa ng valid na Core Slot.
- Sinubukan ang muling pag-okupa ng `OCCUPIED` na Core Slot.
- Sinubukan ang pagpapalaya ng `OCCUPIED` na Core Slot.
- Sinubukan ang muling pagpapalaya ng `FREE` na Core Slot.
- Sinubukan ang invalid at lampas-sa-kapasidad na Core Slot ID.
### Tala
- Ang `UbodContainer` ang nagsisilbing gatekeeper ng Core Slot operations.
- Ang `Core Engine` assignment ay hindi pa kabilang sa bersiyong ito.
- Ang dynamic memory allocation at runtime capacity resizing ay hindi pa sinusuportahan.

## [0.1.8] — Estatikong Kumpulan ng Puwang ng Ubod (*Static Core Slot Pool*)
### Idinagdag
- Idinagdag ang `UbodContainer` para sa pamamahala ng mga Core Slot.
- Idinagdag ang static Core Slot pool na may compile-time `Capacity`.
- Idinagdag ang awtomatikong pagbuo ng sequential Core Slot IDs batay sa `Capacity`.
- Itinakda ang pinapayagang `Capacity` mula sa 2 hanggang 32 Core Slots.
- Idinagdag ang pagkuha ng libreng Core Slot gamit ang `findFree()`.
### Binago
- Inalis ang hard-coded na apat na Core Slot sa `UbodContainer`.
- Ginawang iisang source of truth ang `Capacity` para sa bilang ng Core Slots.
- Pinanatili ang static memory allocation; walang dynamic memory allocation para sa Core Slot pool.
### Sinubukan
- Sinubukan ang static container sa iba't ibang `Capacity`.
- Sinbukan ang pag-occupy at pag-free ng mga Core Slot.
- Sinubukan ang paghahanap ng libreng Slot kapag may available at kapag puno na ang container.
- Sinubukan ang invalid Core Slot ID lookup.
- Sinubukan ang compile-time restriction ng `Capacity`.
### Tala
- Ang `UbodContainer` ay kasalukuyang nakatuon sa MCU/device scope.
- Ang `Capacity` ay itinatakda sa compile time at hindi binabago sa runtime.
- Ang kasalukuyang experimental limit ay 2–32 Core Slots.
- Hindi pa kabilang sa bersiyong ito ang Core engine assignment.

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