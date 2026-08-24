# Ubod

Ang **Ubod** ay isang magaan at static-first na pundasyong software para sa pamamahala ng mga **Core Slot** sa mga resource-constrained embedded system ng **LNDH ecosystem**. Layunin nitong magbigay ng malinaw at mahuhulaang paraan upang pamahalaan ang pagkakakilanlan, lifecycle, availability, pangalan, at paggamit ng mga core resource nang hindi umaasa sa dynamic memory allocation.

Sa kasalukuyang eksperimental na yugto, sinusuportahan ng Ubod ang **Core ID**, **Core Name**, lifecycle states, `FREE` at `OCCUPIED` na availability, at `UbodContainer` na may compile-time capacity. Maaari ring maghanap ng maraming Core Slot na may magkakaparehong pangalan gamit ang `findByName()` at isang caller-owned fixed result buffer.

Ang Ubod ay kasalukuyang nasa **v0.1.x experimental development phase**. Ang mga API at arkitektura ay maaari pang baguhin habang pinag-aaralan ang mas malalim na konsepto ng **Core Engine**, static engine storage, engine attachment, replacement, lifecycle, at diagnostics. Ang pangunahing prinsipyo nito ay: **static, bounded, simple, at angkop sa MCU**.

---

###  Kasaysayan
Lahat ng kapansin-pansing pagbabago sa proyektong ito ay idodokumento sa [file](CHANGELOG.md) na ito.

Ang format ay batay sa [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).
Sa kasalukuyang eksperimental na yugto ng **Ubod**, ang mga bersiyon sa seryeng `v0.1.x` ay nagsisilbing sunod-sunod na development versions. Maaaring magkaroon ng breaking changes, pagbabago sa API, o kawalan ng backward compatibility sa pagitan ng mga bersiyon. Ang version numbering sa yugtong ito ay hindi pa mahigpit na sumusunod sa [Semantic Versioning](https://semver.org/spec/v2.0.0.html).