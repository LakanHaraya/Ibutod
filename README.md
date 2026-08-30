# <span style="font-family: 'Noto Sans Tagalog', sans-serif;">ᜁᜊᜓᜆᜓᜇ᜔</span> Ibútod

**/i•bú•tod/**
*png | [ i+butod ]*
: **pinakaloob, gitna, kalaliman, o pinakasentro**

--- 

Ang **Ibutod** ay isang magaan at static-first na pundasyong software para sa pagbuo at pamamahala ng mga modular na bahagi ng resource-constrained embedded systems ng **LNDH ecosystem**.

Layunin nitong magbigay ng simple, bounded, at mahuhulaang structural foundation para sa mga modular component nang hindi umaasa sa dynamic memory allocation.

> **Static. Bounded. Modular. MCU-oriented.**

---

## Pangunahing Konsepto

Ang kasalukuyang modelo ng Ibutod ay binubuo ng:

```text
Silid
└── Salalayan
    └── Salpakan
        └── Sapad
```

* **Sapad** — bagay na maaaring ikabit sa isang Salpakan.
* **Salpakan** — bounded na puwesto para sa isang Sapad.
* **Salalayan** — grupo ng mga Salpakan na may sariling kapasidad at lokal na state.

Ang **Silid** ay kasalukuyang konseptwal na bahagi lamang ng modelo at hindi pa isang Ibutod class.

---

## Mga Pangunahing Katangian

Sa kasalukuyang development phase, sinusuportahan ng Ibutod ang:

* static storage;
* compile-time configurable capacity;
* local Salpakan identity;
* optional naming;
* Sapad attachment at detachment;
* `FREE` / `OCCUPIED` availability;
* `DISABLED` / `ENABLED` enablement;
* structural accounting at introspection; at
* maraming independiyenteng `Salalayan`.

Halimbawa:

```cpp
Salalayan<4> sensor("Sensor");
Salalayan<3> control("Control");
Salalayan<2> communication("Communication");
```

---

## Disenyo

Ang Ibutod ay idinisenyo para sa mga embedded system kung saan mahalaga ang:

* predictable memory usage;
* maliit at malinaw na abstraction;
* bounded resources;
* modular structure; at
* limitadong runtime overhead.

Ang Ibutod ay kasalukuyang **hindi** isang scheduler, task manager, o execution framework. Ang execution behavior ng mga nakakabit na component ay sadyang nasa labas muna ng kasalukuyang core model.

---

## Development Status

Ang Ibutod ay nasa:

**`v0.1.x — Experimental Development`**

Maaaring magkaroon ng breaking changes, API redesign, at architectural changes sa pagitan ng mga bersiyon habang patuloy na sinusuri ang disenyo.

Ang mga eksperimento at development findings ay nakatala sa `DEVLOG/`, habang ang mga pangunahing pagbabago ay nakatala sa `CHANGELOG.md`.

---

## Pangalan

Ang dating pangalan ng library ay **Ubod**.

**Ibutod** na ngayon ang canonical name ng proyekto.
Pinili ang pangalan batay sa kahulugang:
> **pinakaloob, gitna, kalaliman, o pinakasentro**

na malapit sa konsepto ng *core* na pinagbabatayan ng library.

---

## License

*Tinutukoy pa.*
