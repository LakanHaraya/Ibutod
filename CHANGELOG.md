# Changelog
Lahat ng kapansin-pansing pagbabago sa proyektong ito ay idodokumento sa file na ito.

Ang format ay batay sa [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).
Sa kasalukuyang eksperimental na yugto ng **Ubod**, ang mga bersiyon sa seryeng `v0.1.x` ay nagsisilbing sunod-sunod na development versions. Maaaring magkaroon ng breaking changes, pagbabago sa API, o kawalan ng backward compatibility sa pagitan ng mga bersiyon. Ang version numbering sa yugtong ito ay hindi pa mahigpit na sumusunod sa [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.1.19] — 2026-08-30 — Nakukumpigurang Kapasidad ng Salalayan (*Configurable Salalayan Capacity*)
### Idinagdag
- Idinagdag ang template-based na `Salalayan<Capacity>` upang maitakda ang kapasidad ng bawat Salalayan sa compile-time.
- Idinagdag ang suporta para sa magkakaibang kapasidad ng maraming Salalayan sa iisang application.
- Idinagdag ang compile-time capacity validationmula `1` hanggang `32` Salpakan.
- Idinagdag ang `Salalayan.tpp` para sa template implementation ng `Salalayan`.
### Binago
- Binago ang dating nakapirmeng `Salalayan::Capacity` tungo sa configurable na template parameter.
- Binago ang deklarasyon ng `Salalayan` upang suportahan ang magkakaibang structural capacities bawat instance type.
- Inilipat ang implementation ng `Salalayan` mula `Ubod.cpp` patungo sa template implementation file.

## [0.1.18] — Introspeksiyong Pang-estruktura ng Salalayan (*Salalayan Structural Instrospection*)
### Idinagdag
- Mga structural introspection method para sa `Salalayan`:
    - `enabled()` para magbalik ng bilang ng mga enabled na Salpakan.
    - `disabled()` para magbalik ng bilang ng mga disabled na Salpakan.
    - `isEmpty()` para suriin kung walang nakakabit na Sapad sa anumang Salpakan.
    - `isFull()` para suriin kung lahat ng Salpakan ay may nakakabit na Sapad.
### Binago
- Pinalawak ang kakayahan ng `Salalayan` sa pagsusuri ng kasalukuyang structural state nito.
- Nilinaw ang pagkakaiba ng occupancy at enablement bilang magkahiwalay na dimension ng estado.

## [0.1.17] — Identidad ng Salalayan at Pinamamagitang Kontrol (*Salalayan Identity and Mediated Control*)
### Idinagdag
- Opsiyonal na pangalan para sa `Salalayan`.
- Kakayahang magtakda at mag-clear ng pangalan ng `Salalayan`.
- `enable()` at `disable()` mediation sa `Salalayan` para sa mga `Salpakan` nito.
### Binago
- Pinalawak ang responsabilidad ng `Salalayan` bilang organizational at control boundary para sa mga `Salpakan`.
- Pinanatili ang enablement state bilang katangian ng mismong `Salpakan`.
- Hindi pinapayagang ma-enable ang isang `Salpakan` na walang nakakabit na `Sapad`.

## [0.1.16] — Pagpapagana ng Salpakan (*Salpakan Enablement*)
### Idinagdag
- Idinagdag ang `SalpakanEnablement` bilang hiwalay na konsepto mula sa lifecycle state.
- Idinagdag ang `enable()`, `disable()`, at `isEnabled()` sa `Salpakan`.
- Idinadgdag ang panuntunang hindi maaaring i-enable ang Salpakan kung walang nakakabit na Sapad.
- Idinagdag ang proteksiyon laban sa `detach()` habang naka-enable ang Salpakan.
### Binago
- Ang attachment ay maaari pa ring gawin habang `DISABLED`.
- Ang `attach()` ay hindi awtomatikong nag-e-enable ng Salpakan.
- Ang `detach()` ay maaari lamang gawin kapag `DISABLED`.

## [0.1.15] — Paglipat sa Terminolohiyang Filipino (*Filipino Terminology Migration*)
### Binago
- Pinalitan ang pangunahing terminolngohiya ng Ubod upang gamitin ang mga canonical Filipino abstractions:
    - `UbodContainer` → `Salalayan`
    - `UbodSlot` → `Salpakan`
    - `UbodEngine` → `Sapad`
- Pinalitan ang mga kaugnay na enum:
    - `UbodSlotState` → `SalpakanState`
    - `UbodSlotAvailability` → `SalpakanAvailability`
- Inangkop ang mga API at internal member names upang tumugma sa bagong terminolohiya.
- Pinanatili muna ang English method names upang manatiling malinaw at pamilyar ang operational API habang experimental ang architecture.

## [0.1.14] — Hangganan ng Pagkakabit ng Engine (*Engine Attachment Boundary*)
### Idinagdag
- Idinagdag ang minimal na `UbodEngine` type bilang boundary para sa mga object na maaaring i-attach sa `UbodSLot`
- Idinagdag ang `UbodSlot::attach(UbodEngine* engine)`.
- Idinagdag ang `UbodSlot::detach()`.
- Idinagdag ang `UbodSlot::engine()` para makuha ang kasalukuyang Engine reference.
- Idinagdag ang `UbodSlot::hasEngine()`.
- Idinagdag ang `UbodContainer::detach()`.
### Binago
- Ang Slot availability ay ibinabatay sa pagkakaroon ng attached Engine.
- Ang `OCCUPIED` ay nangangahulugang may attached Engine.
- Ang `FREE` ay nangangahulugang walang attached Engine.
- Ang Slot lifecycle (`begin()` / `update()`) ay nananatiling hiwalay sa Engine attachment.
- Nanatiling non-owning reference ang Engine attachment.

## [0.1.13] — Pagkabit ng Engine sa Core Slot (*Engine Attachment to Core Slot*)
### Idinagdag 
- Idinagdag ang paunang `UbodEngine` attachment model para sa `UbodSlot`.
- Idinagdag ang aktuwal na pag-iimbak ng attached Engine pointer sa loob ng `UbodSlot`.
- Idinagdag ang `engine()` accessor para makuha ang kasalukuyang attached Engine.
- Idinagdag ang const at non-const na bersiyon ng `engine()`.
- Idinagdag ang `hasEngine()` para madaling matukoy kung may nakakabit na Engine sa Slot.
- Inihanay ang `UbodSlotAvailability` sa aktuwal na pagkakaroon ng attached Engine.
- Idinagdag ang Container-level `attached(id, engine)` upang manatiling gatekepeer ang `UbodContainer` sa attachment operation.
## Binago
- Ang dating parameterless na `attach()` ay pinalitan ng `attach(UbodEngine* engine)`.
- Ang `OCCUPIED` state ay hindi na lamang simpleng manual availability marker, kinakatawan na nito ang pagkakaroon ng attached Engine.
- Ang `detach()` ay nagtatanggal ng Engine reference sa Slot sa pamamagitan ng pagtatakda ng pointer sa `nullptr`.
- Ang `detach()` ay hind sumisira o nagde-delete ng Engine, ang pagmamay-ari ng Engine ay nananatili sa application o caller.
- Ang `UbodContainer::attach()` ay tumatanggap na rin ng `UbodEngine*` at ipinapasa ito sa target na Slot.

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

## [0.1.10] — Pagtuklas at Paghahanap ng Puwang ng Ubod (*Core Slot Dicovery and Lookup*)
### Idinagdag
- Idinagdag ang `findByName()` para sa paghahanap ng Core Slots batay sa Core Name.
- Sinusuportahan ang maramihang Core Slots na may magkakaparehong pangalan.
- Gumagamit ng caller-owned fixed result buffer para sa mga resulta.
- Nililimitahan ang bilang ng resulta ayon sa `maxResults`.
- Nanatiling static at bounded ang memory; walang dynamic memory allocation.


## [0.1.9] — API ng Operasyon sa Puwang ng Ubod (*Core Slot Operation API*)
### Idinagdag 
- Idinagdag ang `UbodContainer::occupy(id)` para sa ligtas na pag-okupa ng Core Slot.
- Idinagdag ang `UbodContainer::free(id)` para sa pagpapalaya ng Core Slot.
- Ginawang gatekeeper ang `UbodContainer` para sa mga operasyon sa Core Slot.
- Idinagdag ang proteksiyon laban sa invalid o lampas-sa-kapasidad na Core Slot ID.
### Binago
- Inirerekomenda ang paggamit ng `UbodContainer` operation API sa halip na direktang pagmamanipula ng `UbodCore`.
- Pinanatili ang static memory allocation at compile-time Core Slot capacity.

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

## [0.1.7] — Pagkakaroon ng Puwang ng Ubod (*Core Slot Availability*)
### Idinagdag
- Idinagdag ang `UbodAvailabaility` para sa kalagayan ng Core Slot.
- Idinagdag ang `FREE` at `OCCUPIED` na availability states.
- Idinagdag ang `occupy()`, `free()`, `availability()`, `isFree()`, at `isOccupied()`.
### Binago
- Hiniwalay ang availability ng Core Slot sa lifecycle state ng Ubod.
- Ang bagong Core Slot ay nagsisimula bilang `FRRE`.
- Hindi awtomatikong binabago ng `begin()` ang availability.

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

## [0.1.5] — Pagpapangalan sa Puwang ng Ubod (*Core Slot Naming*)
### Idinagdag
- Nagdagdag ng human-readable name para sa bawat Core Slot.
- Nagdagdag ng `setName()` at `name()` API.
- Gumamit ng fixed-sized character buffer upang maiwasan ang dynamic memory allocation.
- Nagdagdag ng validation para sa null at sobrang habang pangalan.
### Binago
- Pinananatili ang huling Core Name kapag ang Core ay `RELEASED`.
- Hindi na maaaring baguhin ang pangalan ng isang released Core.

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

## [0.1.3] — Pagkakakilanlan ng Instansiya at Pagtukoy ng Magkaparehong ID (*Instance Identity and Duplicate Detection*)
### Idinagdag 
- User-assigned instance ID para sa bawat `UbodCore`.
- Pagpapatunay ng duplicate instance ID.
- `id()` at `isIdValid()` API.
- Paunang instance registry para sa identity validation.

## [0.1.2] — Estado ng Pagtakbo ng Instansiya (*Instance Runtime State*)
### Idinagdag
- Nagdagdag ng `UbodState` para sa lifecycle ng bawat `UbodCore` instance.
- Nagdagdag ng instance-specific runtime state at start time.
- Ginawang instance-relative ang `uptime()`.
- Nagdagdag ng Serial Monitor test para sa dalawang `UbodCore` instance.

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

## [0.1.0] — Munting Balangkas ng Pagpapatakbo (*Minimal Runtime Skeleton*)
### Idinagdag
- Paunang klase ng `UbodCore`.
- Pangunahing lifecycle API:
    - `begin()`
    - `update()`
- Paunang pagsasama ng Ubod sa Arduino `setup()` at `loop()`.
- Paunang library structure sa `lib/Ubod/src/`.