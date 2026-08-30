<p align="center">
    <img src="assets/ibutod-whiteFont-gridBg.svg"
        height="42"
        alt="Ibutod sa Baybayin"
        style="vertical-align: middle;">
</p>

<p align="center">
    <strong>Ang Kaibuturang Lohika</strong>
</p>

[![Latest Release](https://img.shields.io/github/v/release/LakanHaraya/Ibutod?display_name=tag&sort=semver)](https://github.com/LakanHaraya/Ibutod/releases)
[![License: GPL v3](https://img.shields.io/badge/license-GPLv3-blue.svg)](LICENSE)
[![Arduino](https://img.shields.io/badge/Arduino-compatible-00979D)](https://www.arduino.cc/)
[![PlatformIO](https://img.shields.io/badge/PlatformIO-compatible-orange)](https://platformio.org/)
[![Status](https://img.shields.io/badge/status-Experimental-yellow)](https://github.com/LakanHaraya/Ibutod)

> ###### **/i•bú•tod/** png | [ i+butod ] : **pinakaloob, gitna, kalaliman, o pinakasentro**

---

Ang **Ibútod** ay isang magaan, static-first, at microcontroller-oriented na software foundation para sa pagbuo ng modular na bahagi ng resource-constrained embedded systems. Ito ay binubuo bilang bahagi ng **LNDH ecosystem**, ngunit ang mismong mga ideya nito ay sinusubukang manatiling sapat na payak upang mapakinabangan din sa iba pang maliliit at limitadong sistema. 

Nagsimula ang Ibutod mula sa isang payak na tanong: **paano ba natin maipapangkat at mapamamahalaan ang mga modular na bahagi ng isang embedded system nang hindi agad dumedepende sa dynamic memory, malalaking framework, o komplikadong runtime machinery?** Hindi nito sinusubukang lutasin ang lahat. Sa halip, nakatuon ang Ibutod sa pagbibigay ng isang maliit, bounded, at mahuhulaang structural foundation kung saan maaaring magkaroon ng malinaw na lugar ang bawat component sa loob ng isang system.

> **Static. Bounded. Modular. Resource-constrained.**

---

## Ang Modelo

Sa kasalukuyang paghubog nito, inilalarawan ang Ibutod sa pamamagitan ng apat na konsepto:

```text
Silid
└── Salalayan
    └── Salpakan
        └── Sapad
```

Ang **Sapad** ang bagay o component na maaaring ikabit. Ang **Salpakan** naman ang puwesto kung saan ito maaaring ilagay. Ang ilang Salpakan ay bumubuo ng isang **Salalayan**—isang bounded na structural container na may sariling kapasidad at lokal na estado. Samantala, ang **Silid** ay nagsisilbing mas mataas na konseptuwal na hangganan ng modelo. Sa kasalukuyang bersiyon ng Ibutod, hindi pa ito isang aktuwal na class. Bahagi pa lamang ito ng mas malawak na pag-iisip tungkol sa kung paano maaaring buuin at pag-ugnayin ang mga modular na bahagi ng isang sistema.

Sa pinakasimpleng anyo:

* **Sapad** — isang bagay na maaaring ikabit;
* **Salpakan** — isang bounded na puwesto para sa isang Sapad;
* **Salalayan** — isang pangkat ng mga Salpakan na may sariling kapasidad at estado;
* **Silid** — isang mas mataas na konseptuwal na espasyo para sa mga Salalayan.

---

## Ano ang Sinusubukang Gawin?

Ang Ibutod ay hindi naglalayong maging isang kompletong embedded framework. Hindi rin ito isang scheduler, RTOS, task manager, o execution engine. Sadyang may hangganan ang saklaw nito. Ang pangunahing interes ng Ibutod ay ang **estruktura**: kung paano magkaroon ng bounded na mga puwesto, paano ikabit o tanggalin ang mga component, paano malaman ang kanilang availability at enablement state, at paano magkaroon ng ilang independiyenteng structural container sa loob ng iisang embedded application.

Sa kasalukuyang development phase, kabilang sa mga sinusubukang patatagin ang:

* static storage;
* compile-time configurable capacity;
* lokal na identity ng Salpakan;
* optional naming;
* Sapad attachment at detachment;
* `FREE` at `OCCUPIED` availability;
* `DISABLED` at `ENABLED` enablement;
* structural accounting at introspection; at
* maraming independiyenteng `Salalayan`.

Halimbawa, maaaring hatiin ang isang application sa magkakahiwalay na structural domains:

```cpp
Salalayan<4> sensor("Sensor");
Salalayan<3> control("Control");
Salalayan<2> communication("Communication");
```

Ang bawat Salalayan ay may sariling hangganan. Hindi kailangang malaman ng isang bahagi ang lahat ng nasa buong sistema upang magkaroon ng sariling maliit at malinaw na structural context.

---

## Bakit Static at Bounded?

Pangunahing iniisip ng Ibutod ang para sa mga microcontroller at iba pang resource-constrained na kapaligiran kung saan ang pagiging simple at mahuhulaan ay kadalasang mas mahalaga kaysa sa walang hanggang flexibility. Sa halip na palaging umasa sa dynamic allocation, nilalayon ng Ibutod na malaman ang structural capacity nang maaga hangga't maaari.

```cpp
Salalayan<4> sensor;
```

Sa ganitong modelo, malinaw na may apat na Salpakan lamang ang Salalayan. Ang limitasyon ay hindi isang aksidenteng runtime condition, kundi bahagi ito mismo ng disenyo. Hindi ito nangangahulugang ang static approach ang laging pinakamahusay na sagot. Ngunit para sa uri ng mga sistemang pangunahing pinag-eeksperimentuhan ng Ibutod, ang bounded resources ay maaaring magbigay ng mas malinaw na memory expectations, mas simpleng lifecycle, at mas madaling pangangatwiran tungkol sa estado ng system.

---

## Mga Hangganan

Mahalaga rin kung ano ang **hindi** Ibutod. Sa kasalukuyan, hindi nito sinusubukang pamahalaan kung kailan tatakbo ang isang component, gaano kadalas itong tatawagin, o paano ito makikipag-ugnayan sa isang scheduler. Ang execution behavior ay sadyang hindi pa bahagi ng core model. Ang paghihiwalay na ito ay sinasadya. Bago magdagdag ng concurrency, scheduling, events, o iba pang runtime behavior, sinusubukang patatagin muna ng Ibutod ang mas payak na tanong:

> **Paano ba dapat magkaroon ng lugar, hangganan, at estruktura ang mga modular na bahagi ng isang maliit na system?**

Maaaring lumawak ang mga eksperimento sa hinaharap, ngunit hindi nangangahulugang lahat ng susunod na ideya ay kailangang mapasama sa ibutod.

---

## Eksperimental pa rin

Ang Ibutod ay kasalukuyang nasa **`v0.1.x — Experimental Development`**. Ito ay aktibong hinuhubog at sinusuri. Maaaring magbago ang mga pangalan, API, abstraction, at maging ang ilang pangunahing architectural assumptions habang nagpapatuloy ang mga eksperimento. Hindi pa ito nangangako ng stable API. Ang mga development experiments at mga natuklasan habang binubuo ang proyekto ay maaaring matagpuan sa [`DEVLOG/`](DEVLOG/), samantalang ang mga pangunahing pagbabago sa bawat bersiyon ay nakatala sa [`CHANGELOG.md`](CHANGELOG.md).

Sa ngayon, mas mahalaga ang tamang direksiyon kaysa sa mabilis na pagdaragdag ng maraming feature.

---

## Bukás na Proyekto

Ang Ibutod ay isang open-source experimental project. Maaaring gamitin, pag-aralan, baguhin, at paunlarin ang code ayon sa mga tuntunin ng lisensiya nito.

Bagaman nagsimula ito bilang bahagi ng mga eksperimento para sa **LNDH**, bukas ang proyekto sa mga ideya, pagsusuri, at isyu. Hindi nangangahulugan na ang pagiging bukás nito ay awtomatikong mawawala ang direksiyon ng proyekto, kundi ang mga pagbabago sa pangunahing codebase ay dadaan pa rin sa pagsusuri upang mapanatili ang pagiging maliit, malinaw, at may hangganan ng ibutod.

Kung may ideya kang maaaring magpabuti sa disenyo, malugod na pag-aralan, pag-usapan, o subukang i-prototype ito.

---

## Lisensiya

Ang Ibutod ay inilalathala sa ilalim ng **GNU General Public License v3.0 (GPLv3)**.

Tingnan ang [`LICENSE`](LICENSE) para sa buong tuntunin ng lisensiya.

