/*
 * Copyright (C)  NHR@FAU, University Erlangen-Nuremberg.
 * All rights reserved. This file is part of MD-Bench.
 * Use of this source code is governed by a LGPL-3.0
 * license that can be found in the LICENSE file.
 */
#include <atom.h>
#include <parameter.h>

#ifndef __NEIGHBOR_H_
#define __NEIGHBOR_H_
// Interaction masks from GROMACS, things to remember (maybe these confused just me):
//   1. These are not "exclusion" masks as the name suggests in GROMACS, but rather
//      interaction masks (1 = interaction, 0 = no interaction)
//   2. These are inverted (maybe because that is how you use in AVX2/AVX512 masking),
//      so read them from right to left (least significant to most significant bit)
// All interaction mask is the same for all kernels
#define NBNXN_INTERACTION_MASK_ALL 0xffffffffU
// 4x4 kernel diagonal mask
#define NBNXN_INTERACTION_MASK_DIAG 0x08ceU
// 4x2 kernel diagonal masks
#define NBNXN_INTERACTION_MASK_DIAG_J2_0 0x0002U
#define NBNXN_INTERACTION_MASK_DIAG_J2_1 0x002fU
// 4x8 kernel diagonal masks
#define NBNXN_INTERACTION_MASK_DIAG_J8_0 0xf0f8fcfeU
#define NBNXN_INTERACTION_MASK_DIAG_J8_1 0x0080c0e0U
// 2x8 kernel diagonal masks
#define NBNXN_INTERACTION_MASK_DIAG_I2_J8_0 0xfcfeU
#define NBNXN_INTERACTION_MASK_DIAG_I2_J8_1 0xf0f8U
#define NBNXN_INTERACTION_MASK_DIAG_I2_J8_2 0xc0e0U
#define NBNXN_INTERACTION_MASK_DIAG_I2_J8_3 0x0080U
// 2x16 kernel diagonal masks
#define NBNXN_INTERACTION_MASK_DIAG_J16_0 0xfffcfffeU
#define NBNXN_INTERACTION_MASK_DIAG_J16_1 0xfff0fff8U
#define NBNXN_INTERACTION_MASK_DIAG_J16_2 0xffc0ffe0U
#define NBNXN_INTERACTION_MASK_DIAG_J16_3 0xff00ff80U
#define NBNXN_INTERACTION_MASK_DIAG_J16_4 0xfc00fe00U
#define NBNXN_INTERACTION_MASK_DIAG_J16_5 0xf000f800U
#define NBNXN_INTERACTION_MASK_DIAG_J16_6 0xc000e000U
#define NBNXN_INTERACTION_MASK_DIAG_J16_7 0x00008000U

typedef struct {
    int every;
    int ncalls;
    int maxneighs;
    int* numneigh;
    int* numneigh_masked;
    int half_neigh;
    int* neighbors;
    unsigned int* neighbors_imask;
} Neighbor;

typedef void (*BuildNeighborFunction)(Atom*, Neighbor*);
extern BuildNeighborFunction buildNeighbor;

extern void initNeighbor(Neighbor*, Parameter*);
extern void setupNeighbor(Parameter*, Atom*);
extern void binatoms(Atom*);
extern void buildNeighborCPU(Atom*, Neighbor*);
extern void pruneNeighbor(Parameter*, Atom*, Neighbor*);
extern void buildClusters(Atom*);
extern void defineJClusters(Atom*);
extern void binClusters(Atom*);
extern void updateSingleAtoms(Atom*);
#endif
