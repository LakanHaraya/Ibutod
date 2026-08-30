# [0.1.19] — 2026-08-30 
# Nakukumpigurang Kapasidad ng Salalayan
*Configurable Salalayan Capacity*

- [Layunin](#layunin)
- [Sinubukan](#sinubukan)
- [Mga Natuklasan](#mga-natuklasan)
- [Architectural Boundary](#architectural-boundary)
- [Tala](#tala)

---

## Layunin

Suriin ang posibilidad ng paglipat mula sa nakapirmeng kapasidad ng `Salalayan` tungo sa compile-time configurable capacity gamit ang C++ templates.

Layunin ding mapatunayan na maaaring magkaroon ang isang application ng maraming `Salalayan` na may magkakaibang kapasidad habanag nananatiling independiyente ang kanilang mga `Salpakan`.

---

## Sinubukan

### Template Smoke Test

Sinubukan ang iba't ibang kapasidad ng `Salalayan`:

| **Salalayan** | **Kapasidad** | **Resulta** |
| --- | --- | --- |
| `Salalayan<1>` | 1 | PASS | 
| `Salalayan<2>` | 2 | PASS | 
| `Salalayan<4>` | 4 | PASS | 
| `Salalayan<8>` | 8 | PASS | 

Pinatunayan ng smoke test ang sumusunod:

- Tama ang `capacity()` para sa bawat template specialization.
- Independiyente ang accounting ng bawat `Salalayan`.
- Gumagana ang attachment sa iba't ibang kapasidad.
- Gumagana ang enablement sa iba't ibang kapasidad.
- Lokal ang identity ng bawat `Salpakan`.
- Ang out-of-range na ID ay maayos na nire-reject.

---

### Eksperimento Labinsiyam (X19) — Heteroheng Komposisyon ng Salalayan

Bumuo ng tatlong `Salalayan` na may magkakaibang structural capcity:

``` cpp
Sensor<4>
Control<3>
Communication<2>
```

Ginagamit ang mga ito bilang magkakahiwalay na structural groups:

``` txt
Silid 
├── Sensor<4>
│   ├── Salpakan #1 
│   ├── Salpakan #2 
│   ├── Salpakan #3 
│   └── Salpakan #4 
│ 
├── Control<3> 
│   ├── Salpakan #1 
│   ├── Salpakan #2 
│   └── Salpakan #3 
│ 
└── Communication<2> 
    ├── Salpakan #1 
    └── Salpakan #2
```

Sinubukan ang:
- attachment ng magkakaibang `Sapad`;
- selective enablement;
- occupancy accounting;
- enablement accounting;
- local `Salpakan` identity;
- full at non-full structural states; at
- cross-group isolation.

Lahat ng pangunahing pagsusuri ay nagresulta sa `PASS`.

---

## Mga Natuklasan
    
### 1. Independent Structural Capacity

Ang bawat `Salalayan` ay maaaring magkaroon ng sariling compile-time capacity.

``` cpp
Salalayan<4> sensor;
Salalayan<3> control;
Salalayan<2> communication;
```

Hindi kinakailangang magkaroonng magkakaparehong bilang ng `Salpakan` ang bawat structural group.

### 2. Local Salpakan Namespace

Ang `Salpakan ID` ay lokal sa isang `Salalayan`.

Halimbawa:

``` cpp
Sensor/1 
Sensor/2  

Control/1 
Control/2 

Communication/1 
Communication/2
```

### 3. Structural Grouping

Napatunayan na maaaring gamitin ang `Salalayan` bilang structural grouping boundary.

Halimbawa:

- `Sensor` — para sa sensor-related Sapad;
- `Control` — para sa control-related Sapad;
- `Communication` — para sa communication-related Sapad.

Ang grouping ay nananatiling structural at hindi pa nagpapakilala ng execution o scheduling behavior.

### 4. Local Independence

Ang bawat `Salalayan` ay may sariling:

- capacity;
- `Salpakan` collection;
- occupancy accounting;
- enablement accounting; at
- local identity namespace.

Ang pagbabago sa isang `Salalayan` ay hindi nakaaapekto sa accounting o enablement state ng iba.

--- 

## Architectural Boundary

Hindi pa idinagdag sa bersiyong ito ang:

- global registry ng mga `Salalayan`;
- global `Salpakan` identity;
- `Silid` class;
- dynamic allocation;
- `Sapad` lifecycle contract;
- scheduler;
- cross-`Salalayan` communication; o
- system-wide policy. 

---

## Tala

Ang `v0.1.19` ay nagmarka ng paglipat mula sa isang fixed-capacity container patungo sa isang compile-time configurable structural grouping model.

Sa puntong ito, ang `Salalayan` ay hindi na lamang simpleng container ng mga `Salpakan`. Ito ay nagsisilbi bilang isang independiyenteng structural boundary na may:

- lokal na namespace;
- configurable capacity;
- mediated attachment at enablement control; at
- structural introspection.

Ang susunod na hakbang ay isang architectural review ng kasalukuyang mga responsabilidad at hangganan ng `Sapad`, `Salpakan`, at `Salalayan` bago magdagdag ng panibagong abstraction o behavior.