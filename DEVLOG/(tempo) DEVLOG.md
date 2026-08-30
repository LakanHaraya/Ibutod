# DEVLOG

Talaan ng mga eksperimento, pagsusuri, obserbasyon, at architectural decisions sa pagpapaunlad ng Ubod.

---

## [0.1.19] — 2026-08-30 — Nakukumpigurang Kapasidad ng Salalayan (*Configurable Salalayan Capacity*)

## [0.1.18] — Introspeksiyong Pang-estruktura ng Salalayan (*Salalayan Structural Instrospection*)
### Sinubukan
- Initial structural state ng Salalayan.
- Occupancy accounting:
    - `used() + free() == capacity()`
- Enablement accounting:
    - `enabled() + disabled() == capacity()`
- Relationship ng occupancy at enablement:
    - `enabled() <= used()`
- Pagkakaiba ng `FULL` structural state at operational enablement.
- Structural state pagkatapos ng attachment, enablement, disablement, at detachment.
### Tala
- Ang `FULL` ay tumutukoy lamang sa attachment occupancy at hindi nangangahulugang lahat ng Salpakan ay enabled.
- Ang isang occupied na Salpakan ay maaaring manatiling disabled.
- Hindi pa rin nagdadagdag ang Ubod ng Sapad lifecycle, execution behavior, scheduler, o system policy.
- Nanatiling magaan at structural ang responsabilidad ng Salalayan.

## [0.1.17] — Identidad ng Salalayan at Pinamamagitang Kontrol (*Salalayan Identity and Mediated Control*)
### Sinubukan
- Opsiyonal na pagpapangalan sa `Salpakan`
- Pagtakda at pag-clear ng pangalan ng `Salalayan`.
- Salalayan-mediated enable at disable ng `Salpakan`.
- Pagtanggi sa pag-enable nang walang lamang `Salpakan`.
- Boundary checking para sa invalid na Salpakan ID.
- Pagpapanatili ng attachment identity habang nagbabago ang enablement.
- Detachment ng `Sapad` mula sa disabled na `Salpakan`.
### Tala
- Walang lifecycle mechanism na idinagdag sa `Salalayan`.
- Ang `Salalayan` ay hindi nagmamay-ari o sumisira sa mga `Sapad`.
- Ang enablement ay nananatiling hiwalay na konsepto mula sa attachment.
- Ang runtime execution contract ng `Sapad` ay hindi pa saklaw ng bersiyong ito.

## [0.1.16] — Pagpapagana ng Salpakan (*Salpakan Enablement*)
### Sinubukan
- Pagtanggi sa `enable()` kapag walang Sapad.
- Pag-enable ng Salpakan na may nakakabit na Sapad.
- Pagtanggi sa paulit-ulit na `enable()`
- Pagtanggi sa `detach()` habang `ENABLED`.
- `disable()` bago ang `detach()`.
- Muling pag-attach matapos ang `detach()`.
- Invariant: **Walang Sapad => FREE + DISABLED**.
### Tala
- Ang enablement ay kasalukuyang responsabilidad ng `Salpakan`.
- Wala pa ring lifecycle o execution contract ang `Sapad`.
- Wala pang lifecycle management ang `Salalayan`.
- Nanatiling magaan at experimental, walang idinagdag na scheduler, dependecy manager, hot-swap, OTA, o iba pang higher-level mechanism.

## [0.1.15] — Paglipat sa Terminolohiyang Filipino (*Filipino Terminology Migration*)
### Napatunayan
- Gumagana nang tama ang attachment at detachment ng isang `Sapad` sa isang `Salpakan`.
- Nanatiling persistent ang identity ng isang `Salpakan` kahit walang nakakabit na `Sapad`.
- Napatunayan ang isang-Sapad-bawat-Salpakan attachment invariant.
- Gumagana ang reattachment ng `Sapad` matapos ang detachment.
- Gumagana ang accounting ng `Salalayan` gamit ang `capacity()`, `used()`, at `free()`.
- Gumagana ang paghahanap ng libreng `Salpakan`.
- Gumagana ang lookup ng `Salalayan` batay sa pangalan.
- Napatunayan na ang `Salpakan` IDs ay local sa isang `Salalayan`.
- Napatunayan na maaaring magkaroon ng maraming `Salalayan` na parehong may `Salapakan #1`, ngunit magkaibang object ang mga ito.
## Tala
- Itinatag ang canonical conceptual hierarchy: **Silid → Salalayan → Salpakan → Sapad**
- Ang `Silid` ay nananatiling conceptual system/environment boundary at wala pang kinakailangang class implementation.
- Ang `Salalayan` ang nag-oorganisa at naglalaman ng mga `Salpakan`.
- Ang `Salpakan` ang persistent modular attachment boundary.
- Ang `Sapad` ang functional unit na maaaring ikabit sa isang `Salpakan`.
- Ang attachment ay nagtatatag lamang ng modular relationship at hindi pa awtomatikong nagsisimula ng execution.
- Ang runtime execution contract ng `Sapad` ay hindi pa ipinapatupad at ipinagpaliban para sa susunod na experimental iterations.

## [0.1.14] — Hangganan ng Pagkakabit ng Engine (*Engine Attachment Boundary*)
### Sinubukan
- Pagtanggi sa `nullptr` Engine attachment.
- Matagumpay na attachment ng Engine.
- Pagpapatunay ng Engine identity gamit ang `engine()`.
- Pagtanggi sa pagpapalit ng kasalukuyang attached Engine.
- Detachment ng Engine.
- Pagtanggi sa double detach.
- Muling pag-attach ng ibang Engine pagkatapos ng detach.
- Container `used()` at `free()` accounting.
- Pagpapatunay ng Engine-ay-`OCCUPIED` invariant.
- Pagpapatunay ng Walang-Engine-ay-`FREE` invariant.
- Pagpapatunay na hindi nililikha o winawasak ng Ubod ang Engine.
### Tala
- Ang `UbodEngine` ay minimal type boundary pa lamang, wala pa itong execution contract.
- Ang Engine ay nililikha at pinamamahalaan sa labas ng Ubod.
- Ang `UbodSlot` ay nag-iimbak lamang ng Engine address at hindi nagmamay-ari ng Engine object.
- Ang `detach()` ay nag-aalis lamang ng attachment reference.
- Hindi pa tinutukoy kung maaaring i-attach ang iisang Engine sa maraming Slot.
- Hindi pa tinutukoy ang Engine execution, scheduling, `run()`/`stop()`, o Engine lifecycle callbacks.
- Nanatiling static at bounded ang memory model.

## [0.1.13] — Pagkabit ng Engine sa Core Slot (*Engine Attachment to Core Slot*)
## Sinubukan
- Pagkuha ng Slot mula sa `UbodContainer`.
- Pagpapatunay na walang Engine ang bagong Slot.
- Pagtanggi sa `attach(nullptr)`.
- Matagumpay na pag-attach ng valid na `UbodEngine`.
- Pagpapatunay ng pointer identity ng attached Engine.
- Pagtanggi sa pag-attach ng panibagong Engine sa `OCCUPIED` na Slot.
- Matagumpay na `detach()` ng Engine mula sa Slot.
- Pagpapatunay na nagiging `nullptr` ang Engine reference pagkatapos ng detach.
- Muling pag-attach ng ibang Engine pagkatapos maging `FREE` ang SLot.
- Paggamit ng `UbodContainer` bilang gatekeeper para sa `attach()` at `detach()` operations.
## Tala
- Ang `UbodSlot` ay hindi nagmamay-ari ng attached `UbodEngine`.
- Hindi responsable ang `UbodSlot` sa paglikha o pagsira ng Engine object.
- Ang `detach()` ay nagtatanggal lamang ng binding sa pagitan ng Slot at Engine.
- Sa bersiyong ito, ang Engine attachment ay pointer-based at hindi gumagamit ng dynamic memory allocation.
- Ang `OCCUPIED` ay inaasahang tumutugma sa pagkakaroon ng valid na attached Engine pointer.
- Hindi pa tinutukoy ang execution model, scheduling model, Engine identity, o lifecycle contract ng `UbodEngine`.
- Ang pagbabago sa `attach()` API ay isang breaking API change mula sa naunang bersiyon.

## [0.1.12] — Paglilinaw ng Semantika ng Attachment ng Slot (*Slot Attachment Semantics Alignment*)
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
### Tala
- Normal naming. 
- Walang empty at whitespace-only names.
- Maximum name length.
- Duplicate names.
- Core renaming.
- Name retention pagkatapos ng `release()`.

## [0.1.5] — Pagpapangalan sa Puwang ng Ubod (*Core Slot Naming*)
### Tala
- Pinapayagan ang magkaparehong Core Name dahil ang Core ID pa rin ang natatanging identity ng slot.
- Napanatili ang kasalukuyang Core ID at lifecycle behavior.   

## [0.1.4] — Ikot-Buhay ng Instansiya at Pagpapalaya ng Pagkakakilanlan (*Instance Lifecycle and Identity Release*)
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
### Sinubukan
- Dalawang valid na instance na may magkakaibang ID.
- Duplicate ID sa dalawang `UbodCore` instance.
- Pagpigil sa initialization ng instance na may duplicate ID.
### Tala
- Ang instance ID ay nakalaan para sa **MCU/device** scope.
- Eksperimental pa ang registry at identity lifecycle.

## [0.1.2] — Estado ng Pagtakbo ng Instansiya (*Instance Runtime State*)
### Sinubukan
- Independent initialization ng `coreA` at `coreB`.
- Magkaibang initialization time at uptime ng bawat instance.
- Paglipat ng bawat instance mula sa `READY` patungong `RUNNING`.
### Tala
- Shared pa rin ang platform clock (`millis()`).
- Eksperimental pa rin ang lifecycle API at maaaring baguhin sa mga susunod na bersiyon.

## [0.1.1] — Eksperimento para sa Maramihang Instansiya (*Multi-Instance Experiment*)
### Sinubukan
- Dalawang instansiya ng `UbodCore` sa iisang Arduino Nano ESP32.
- Magkahiwalay na pagtawag ng `begin()` at `update()` para sa bawat instansiya.
- Pagbasa ng runtime information sa pamamagitan ng Serial Monitor.

## [0.1.0] — Munting Balangkas ng Pagpapatakbo (*Minimal Runtime Skeleton*)
### Sinubukan
- Pagbuo gamit ang PlatformIO
- Pag-upload sa Arduino Nano ESP32
- Pangunahing runtime integration sa Arduino Framework.
### Tala
- Ang bersiyon ito ay nagsilbing panimulang runtime skeleton.
- Hindi pa tinukoy bilang pangwakas ang arkitektura ng Ubod.