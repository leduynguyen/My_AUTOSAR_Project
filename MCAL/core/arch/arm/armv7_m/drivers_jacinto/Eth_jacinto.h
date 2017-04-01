/*-------------------------------- Arctic Core ------------------------------
 * Copyright (C) 2013, ArcCore AB, Sweden, www.arccore.com.
 * Contact: <contact@arccore.com>
 *
 * You may ONLY use this file:
 * 1)if you have a valid commercial ArcCore license and then in accordance with
 * the terms contained in the written license agreement between you and ArcCore,
 * or alternatively
 * 2)if you follow the terms found in GNU General Public License version 2 as
 * published by the Free Software Foundation and appearing in the file
 * LICENSE.GPL included in the packaging of this file or here
 * <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>
 *-------------------------------- Arctic Core -----------------------------*/
#ifndef ETH_JACINTO_H_
#define ETH_JACINTO_H_

#include "Arc_Types.h"

#define GMAC_SW_BASE           (0x48484000U + L3_OFFSET)
#define GMAC_SW_CPPI_RAM_LEN   0x2000u

/* SL macros */

#define ETH_GMAC_SW_SL_MACCTRL_RX_CMF_EN                     (0x01000000U)
#define ETH_GMAC_SW_SL_MACCTRL_RX_CSF_EN                     (0x00800000U)
#define ETH_GMAC_SW_SL_MACCTRL_RX_CEF_EN                     (0x00400000U)
#define ETH_GMAC_SW_SL_MACCTRL_TX_SHORT_GAP_LIM_EN           (0x00200000U)
#define ETH_GMAC_SW_SL_MACCTRL_EXT_EN                        (0x00040000U)
#define ETH_GMAC_SW_SL_MACCTRL_GIG_FORCE                     (0x00020000U)
#define ETH_GMAC_SW_SL_MACCTRL_IFCTL_B                       (0x00010000U)
#define ETH_GMAC_SW_SL_MACCTRL_IFCTL_A                       (0x00008000U)
#define ETH_GMAC_SW_SL_MACCTRL_CMD_IDLE                      (0x00000800U)
#define ETH_GMAC_SW_SL_MACCTRL_TX_SHORT_GAP_EN               (0x00000400U)
#define ETH_GMAC_SW_SL_MACCTRL_GIG                           (0x00000080U)
#define ETH_GMAC_SW_SL_MACCTRL_TX_PACE                       (0x00000040U)
#define ETH_GMAC_SW_SL_MACCTRL_GMII_EN                       (0x00000020U)
#define ETH_GMAC_SW_SL_MACCTRL_TX_FLOW_EN                    (0x00000010U)
#define ETH_GMAC_SW_SL_MACCTRL_RX_FLOW_EN                    (0x00000008U)
#define ETH_GMAC_SW_SL_MACCTRL_MTEST                         (0x00000004U)
#define ETH_GMAC_SW_SL_MACCTRL_LOOPBACK                      (0x00000002U)
#define ETH_GMAC_SW_SL_MACCTRL_FULLDUPLEX                    (0x00000001U)

#define ETH_GMAC_SW_SL_RX_MAXLEN_MASK                        (0x00003FFFU)

/* Desc masks */
#define ETH_GMAC_SW_DSC_RX_BUF_LEN_MASK                      (0x000007FFu)

#define ETH_GMAC_SW_DSC_RX_BUF_OFFSET_MASK                   (0x07FF0000u)

#define ETH_GMAC_SW_DSC_TX_BUF_LEN_MASK                      (0x0000FFFFu)
#define ETH_GMAC_SW_DSC_TX_BUF_OFFSET_MASK                   (0xFFFF0000u)
#define ETH_GMAC_SW_DSC_PKT_LEN_MASK                         (0x000007FFu)

/* Desc Packet Flags */
#define ETH_GMAC_SW_DSC_FLAG_NOMATCH                         (0x00010000u)
#define ETH_GMAC_SW_DSC_FLAG_SOP                             (0x80000000u)
#define ETH_GMAC_SW_DSC_FLAG_EOP                             (0x40000000u)
#define ETH_GMAC_SW_DSC_FLAG_OWNER                           (0x20000000u)
#define ETH_GMAC_SW_DSC_FLAG_EOQ                             (0x10000000u)
#define ETH_GMAC_SW_DSC_FLAG_TDOWNCMPLT                      (0x08000000u)
#define ETH_GMAC_SW_DSC_FLAG_PASSCRC                         (0x04000000u)
#define ETH_GMAC_SW_DSC_FLAG_LONG                            (0x02000000u)
#define ETH_GMAC_SW_DSC_FLAG_SHORT                           (0x01000000u)
#define ETH_GMAC_SW_DSC_FLAG_MAC_CTL                         (0x00800000u)
#define ETH_GMAC_SW_DSC_FLAG_OVERRUN                         (0x00400000u)
#define ETH_GMAC_SW_DSC_FLAG_PKT_ERROR_MASK                  (0x00300000u)
#define ETH_GMAC_SW_DSC_FLAG_RX_VLAN_ENCAP                   (0x00080000u)
#define ETH_GMAC_SW_DSC_FLAG_FROM_PORT_MASK                  (0x00070000u)
#define ETH_GMAC_SW_DSC_FLAG_TO_PORT_EN                      (0x00100000u)
#define ETH_GMAC_SW_DSC_FLAG_TO_PORT_MASK                    (0x00030000u)
#define ETH_GMAC_SW_DSC_FLAG_TO_PORT_SHIFT                   (16u)
#define ETH_GMAC_SW_DSC_FLAG_PKT_SINGLE                      (ETH_GMAC_SW_DSC_FLAG_SOP | ETH_GMAC_SW_DSC_FLAG_EOP)

#define ETH_GMAC_SW_DSC_RX_BUFFER_OFFSET_MASK                (0x0000FFFFu)
#define ETH_GMAC_SW_RX_VLAN_ENCAP                            (0x00000004U)
#define ETH_GMAC_SW_VLAN_AWARE                               (0x00000002U)
#define ETH_GMAC_SW_FIFO_LOOPBACK                            (0x00000001U)

/* Interrupt related macros */
#define ETH_GMAC_SW_TRXn_PEND_MASK                           (0x00000001U)
#define ETH_GMAC_C0_TRXn_EN                                  (0x00000001U)

#define ETH_GMAC_SW_HOST_ERR_INT_MASK                        (0x00000002U)
#define ETH_GMAC_SW_STAT_INT_MASK                            (0x00000001U)

#define ETH_GMAC_SW_RXn_THRESH_PEND_MASK                     (0x00000100U)
#define ETH_GMAC_C0_RXn_THRESH_EN                            (0x00000001U)

#define	ETH_GMAC_SW_MDIO_USERINT                             (0x00000001U)
#define	ETH_GMAC_SW_MDIO_LINKINT                             (0x00000002U)
#define	ETH_GMAC_SW_HOST_PENDINT                             (0x00000004U)
#define	ETH_GMAC_SW_STAT_PENDINT                             (0x00000008U)
#define	ETH_GMAC_SW_EVNT_PENDINT                             (0x00000010U)

#define ETH_GMAC_SW_INT_STAT_MASK                            (0x000000FFU)
#define	ETH_GMAC_SW_CPDMA_EOI_RX_THRESH_PULSE                (0u)
#define	ETH_GMAC_SW_CPDMA_EOI_RX_PULSE                       (1u)
#define	ETH_GMAC_SW_CPDMA_EOI_TX_PULSE                       (2u)
#define	ETH_GMAC_SW_CPDMA_EOI_MISSL                          (3u)

/* priorities and channel assignments */
#define ETH_GMAC_SW_PORT_MAX_PRI_VAL                         (7u)
#define ETH_GMAC_SW_PORT_TX_PRI_MAP_SHIFT                    (2u)
#define ETH_GMAC_SW_QUEUE_PRIORITY_SHIFT                     (4u)
#define ETH_GMAC_SW_QUEUE_PRIORITY_MASK                      (0x00000003U)
#define ETH_GMAC_SW_PORT_TX_PRI1_MAP_SHIFT                   (ETH_GMAC_SW_PORT_TX_PRI0_MAP_SHIFT+ 2u)
#define ETH_GMAC_SW_PORT_TX_PRI2_MAP_SHIFT                   (ETH_GMAC_SW_PORT_TX_PRI1_MAP_SHIFT+ 2u)
#define ETH_GMAC_SW_PORT_TX_PRI3_MAP_SHIFT                   (ETH_GMAC_SW_PORT_TX_PRI2_MAP_SHIFT+ 2u)
#define ETH_GMAC_SW_PORT_TX_PRI4_MAP_SHIFT                   (ETH_GMAC_SW_PORT_TX_PRI3_MAP_SHIFT+ 2u)
#define ETH_GMAC_SW_PORT_TX_PRI5_MAP_SHIFT                   (ETH_GMAC_SW_PORT_TX_PRI4_MAP_SHIFT+ 2u)
#define ETH_GMAC_SW_PORT_TX_PRI6_MAP_SHIFT                   (ETH_GMAC_SW_PORT_TX_PRI5_MAP_SHIFT+ 2u)
#define ETH_GMAC_SW_PORT_TX_PRI7_MAP_SHIFT                   (ETH_GMAC_SW_PORT_TX_PRI6_MAP_SHIFT+ 2u)
#define ETH_GMAC_SW_CPDMA_CHANNEL_MAP_SHIFT                  (4u)
#define ETH_GMAC_SW_CPDMA_CHANNEL_MAP_PORT2_SHIFT            (16u)
#define ETH_GMAC_SW_CPDMA_CHANNEL_MASK                       (0x00000007U)
#define ETH_GMAC_SW_SL_RX_PRI_MAP_SHIFT                      (4u)
#define ETH_GMAC_SW_SL_RX_PRI_MAP_MASK                       (0x00000007U)

/* ALE */
#define ETH_GMAC_SW_ALE_ENABLE                               (0x80000000U) /* Enable ALE */
#define ETH_GMAC_SW_ALE_CLEAR_TABLE                          (0x40000000U) /* Clear ALE address table */
#define ETH_GMAC_SW_ALE_AGE_OUT_NOW                          (0x20000000U) /* (free up) any ageable table entry that does not have a set touch bit */
#define ETH_GMAC_SW_ALE_EN_P0_UNI_FLOOD                      (0x00000100U) /* flood unknown unicast packets to host port (p0) */
#define ETH_GMAC_SW_ALE_LEARN_NO_VID                         (0x00000080U) /* 1 - VID is not learned with the source address (source address is not tied to VID).*/
#define ETH_GMAC_SW_ALE_EN_VID0_MODE                         (0x00000040U) /* Enable VLAN ID = 0 Mode  0x00 - Process the packet with VID = PORT_VLAN[11:0]. 1 - Process the packet with VID = 0.*/
#define ETH_GMAC_SW_ALE_ENABLE_OUI_DENY                      (0x00000020U) /* When set this bit indicates that a packet with a non OUI table entry matching source address will be dropped */
#define ETH_GMAC_SW_ALE_BYPASS                               (0x00000010U) /* ALE Bypass */
#define ETH_GMAC_SW_ALE_RATE_LIMIT_TX                        (0x00000008U) /* Rate Limit Transmit mode */
#define ETH_GMAC_SW_ALE_VLAN_AWARE                           (0x00000004U) /* 0 - Flood if VLAN not found 1 - Drop packet if VLAN not found */
#define ETH_GMAC_SW_ALE_ENABLE_AUTH_MODE                     (0x00000002U) /* Enable MAC Authorization Mode */
#define ETH_GMAC_SW_ALE_ENABLE_RATE_LIMIT                    (0x00000001U) /* Enable Broadcast and Multicast Rate Limit */

#define ETH_GMAC_SW_ALE_TAB_WRITE_RDZ                        (0x80000000U)
#define ETH_GMAC_SW_ALE_TAB_ENTRY_POINTER                    (0x000003FFU)

#define ETH_GMAC_SW_TABL_ENTRY_UNKNOWN                       (75u)  //(0x00000400U) actual whole parsing takes time
/* Free entry / common */
#define ETH_GMAC_SW_TABL_ENTRY1_MCAST_FWD_STATE_MASK         (0xC0000000U)
#define ETH_GMAC_SW_TABL_ENTRY1_FWD_STATE_SHIFT              (30u)
#define ETH_GMAC_SW_TABL_ENTRY1_TYPE_MASK                    (0x30000000U)
#define ETH_GMAC_SW_TABL_ENTRY1_TYPE_SHIFT                   (28u)
#define ETH_GMAC_SW_TABL_ENTRY1_VID_MASK                     (0x0FFF0000U)
#define ETH_GMAC_SW_TABL_ENTRY1_VID_SHIFT                    (16u)
#define ETH_GMAC_SW_TABL_ENTRY1_ADRS_32_47_MASK              (0x0000FFFFU)

/* For VLAN/Multicast Address Table Entry */
#define ETH_GMAC_SW_TABL_ENTRY2_SUPER                        (0x00000002U)
#define ETH_GMAC_SW_TABL_ENTRY2_PORT_MASK                    (0x0000001CU)


/* For VLAN/Unicast Address Table Entry */
#define ETH_GMAC_SW_TABL_ENTRY1_UNICAST_TYPE_MASK            (0xC0000000U)
#define ETH_GMAC_SW_TABL_ENTRY2_PORT_NUM_MASK                (0x0000000CU)
#define ETH_GMAC_SW_TABL_ENTRY2_PORT_NUM_SHIFT               (2u)
#define ETH_GMAC_SW_TABL_ENTRY2_BLOCK                        (0x00000002U)
#define ETH_GMAC_SW_TABL_ENTRY2_SECURE                       (0x00000001U)

/* For VLAN Table Entry */
#define ETH_GMAC_SW_TABL_ENTRY0_VLAN_MEMBER_LIST_MASK        (0x00000007U)
#define ETH_GMAC_SW_TABL_ENTRY0_UNREG_MCAST_FLOOD_MASK       (0x00000700U)
#define ETH_GMAC_SW_TABL_ENTRY0_REG_MCAST_FLOOD_MASK         (0x00070000U)
#define ETH_GMAC_SW_TABL_ENTRY0_FORCE_UNTAGGED_EGRESS_MASK   (0x07000000U)
#define ETH_GMAC_SW_VLAN_TABL_UNREG_MCAST_FLOOD_SHIFT        (8u )
#define ETH_GMAC_SW_VLAN_TABL_REG_MCAST_FLOOD_SHIFT          (16u)
#define ETH_GMAC_SW_VLAN_TABL_FORCE_UNTAGGED_EGRESS_SHIFT    (24u)



#define ETH_GMAC_MCAST_FWD_STATE_BLOCK_FORWARD_LEARN         (1u)
#define ETH_GMAC_MCAST_FWD_STATE_FORWARD_LEARN               (2u)
#define ETH_GMAC_MCAST_FWD_STATE_FORWARDING                  (3u)


#define ETH_GMAC_SW_ALE_PORT_STATE_MASK                      (0x00000003U)
#define ETH_GMAC_SW_ALE_PORT_STATE_DISABLE                   (0x00000000U)
#define ETH_GMAC_SW_ALE_PORT_STATE_BLOCK                     (0x00000001U)
#define ETH_GMAC_SW_ALE_PORT_STATE_LEARN                     (0x00000002U)
#define ETH_GMAC_SW_ALE_PORT_STATE_FORWARD                   (0x00000003U)
#define ETH_GMAC_SW_ALE_PORT_DROP_UNTAGGED                   (0x00000004U) /* Drop untagged ingress packets */
#define ETH_GMAC_SW_ALE_PORT_VID_INGRESS_CHECK               (0x00000008U) /* Drop packets with unknown VIDs */
#define ETH_GMAC_SW_ALE_PORT_NO_LEARN                        (0x00000010U)
#define ETH_GMAC_SW_ALE_PORT_NO_SA_UPDATE                    (0x00000020U) /* no source port number update */
#define ETH_GMAC_SW_ALE_PORT_MCAST_LIMIT_MASK                (0x00FF0000U)
#define ETH_GMAC_SW_ALE_PORT_MCAST_LIMIT_SHIFT               (16u)
#define ETH_GMAC_SW_ALE_PORT_BCAST_LIMIT_MASK                (0xFF000000U)
#define ETH_GMAC_SW_ALE_PORT_BCAST_LIMIT_SHIFT               (24u)

#define ETH_GMAC_SW_ALE_PORT_BCAST_LIMIT                     (25u)

#define ETH_GMAC_MCAST_ADDR_VALIDATE_BYTE                    (0u)
#define ETH_GMAC_MCAST_ADDR_MASK                             (1u)


#define ETH_GMAC_SW_ALE_PORTX_TX_IN_CTL_SEL_MASK             (0x00030000U)

#define ETH_GMAC_SW_ALE_NORMAL_PRIO_MODE                     (0u)
#define ETH_GMAC_SW_ALE_DUAL_MAC_MODE                        (1u)
#define ETH_GMAC_SW_ALE_RATE_LIMIT_MODE                      (2u)
#define ETH_GMAC_SW_ALE_MODE_SHIFT                           (16u)


#define ETH_GMAC_SW_PORT_PRI_MASK                            (0x0000E000U)
#define ETH_GMAC_SW_PORT_PRI_SHIFT                           (13u)
#define ETH_GMAC_SW_PORT_CFI_MASK                            (0x00001000U)
#define ETH_GMAC_SW_PORT_CFI_SHIFT                           (12u)
#define ETH_GMAC_SW_PORT_VID_MASK                            (0x00000FFFU)

/* MDIO / MDC */
#define ETH_GMAC_SW_MDIO_IDLE                                (0x80000000U)
#define ETH_GMAC_SW_MDIO_ENABLE                              (0x40000000U)
#define ETH_GMAC_SW_MDIO_HIGHEST_USER_CH_MASK                (0x1F000000U)
#define ETH_GMAC_SW_MDIO_PREAMBLE_DISABLE                    (0x00100000U)
#define ETH_GMAC_SW_MDIO_FAULT                               (0x00080000U)
#define ETH_GMAC_SW_MDIO_FAULTENB                            (0x00040000U)
#define ETH_GMAC_SW_MDIO_INTTESTENB                          (0x00020000U)
#define ETH_GMAC_SW_MDIO_CLK_DIV_MASK                        (0x0000FFFFU)

#define ETH_GMAC_SW_MDIO_USERACCESS_GO                       (0x80000000U)
#define ETH_GMAC_SW_MDIO_USERACCESS_WRITE                    (0x40000000U)
#define ETH_GMAC_SW_MDIO_USERACCESS_ACK                      (0x20000000U)
#define ETH_GMAC_SW_MDIO_USERACCESS_REG_MASK                 (0x03E00000U)
#define ETH_GMAC_SW_MDIO_USERACCESS_PHYADR_MASK              (0x001F0000U)
#define ETH_GMAC_SW_MDIO_USERACCESS_DATA_MASK                (0x0000FFFFU)
#define ETH_GMAC_SW_MDIO_USERACCESS_REG_SHIFT                (21u)
#define ETH_GMAC_SW_MDIO_USERACCESS_PHYADR_SHIFT             (16u)


#define ETH_GMAC_MAIN_CLK                                    (125000000U)
#define ETH_GMAC_MDC_CLK                                     (2500000U)

/* CPDMA macros */
#define ETH_GMAC_SW_CPDMA_TX_EN                              (0x00000001U)
#define ETH_GMAC_SW_CPDMA_RX_EN                              (0x00000001U)
#define ETH_GMAC_CPDMA_EOI_VECTOR_MASK                       (0x0000001FU)

/* CPSW macros */
#define GMAC_SW_SPSW_P0_STAT_EN                              (0x00000001U)
#define GMAC_SW_SPSW_P1_STAT_EN                              (0x00000002U)
#define GMAC_SW_SPSW_P2_STAT_EN                              (0x00000002U)

#define ETH_GMAC_SW_SOFT_RESET                               (0x00000001U)

/*lint -save -e834 -e9050 */ /* This is for clarity */
/* GMAC_SW registers */
struct GmacSw_reg {
    struct{
        vuint32_t CPSW_ID_VER; /* R 32 0x0000 0000 0x4848 4000 */
        vuint32_t CPSW_CONTROL; /*  RW 32 0x0000 0004 0x4848 4004 */
        vuint32_t CPSW_SOFT_RESET; /* RW 32 0x0000 0008 0x4848 4008 */
        vuint32_t CPSW_STAT_PORT_EN; /*RW 32 0x0000 000C 0x4848 400C */
        vuint32_t CPSW_PTYPE; /* RW 32 0x0000 0010 0x4848 4010 */
        vuint32_t CPSW_SOFT_IDLE; /* RW 32 0x0000 0014 0x4848 4014 */
        vuint32_t CPSW_THRU_RATE;  /* RW 32 0x0000 0018 0x4848 4018 */
        vuint32_t CPSW_GAP_THRESH; /* RW 32 0x0000 001C 0x4848 401C */
        vuint32_t CPSW_TX_START_WDS; /* RW 32 0x0000 0020 0x4848 4020 */
        vuint32_t CPSW_FLOW_CONTROL; /* RW 32 0x0000 0024 0x4848 4024 */
        vuint32_t CPSW_VLAN_LTYPE; /* RW 32 0x0000 0028 0x4848 4028 */
        vuint32_t CPSW_TS_LTYPE; /* RW 32 0x0000 002C 0x4848 402C */
        vuint32_t CPSW_DLR_LTYPE; /* RW 32 0x0000 0030 0x4848 4030 */
        vuint32_t CPSW_EEE_PRESCALE; /* RW 32 0x0000 0034 0x4848 4034 */
    }SS;
    vuint32_t SS_Padding[(0x4100 - 0x4034 - 0x4)/4];
    struct{
        vuint32_t CONTROL; /*  RW 32 0x0000 0000 0x4848 4100 */
        vuint32_t CONTROL_Padding[(0x4108 - 0x4100 - 0x4)/4];
        vuint32_t MAX_BLKS; /*  RW 32 0x0000 0008 0x4848 4108 */
        vuint32_t BLK_CNT; /*  RW 32 0x0000 000C 0x4848 410C */
        vuint32_t TX_IN_CTL; /*  RW 32 0x0000 0010 0x4848 4110 */
        vuint32_t PORT_VLAN; /*  RW 32 0x0000 0014 0x4848 4114 */
        vuint32_t TX_PRI_MAP; /*   RW 32 0x0000 0018 0x4848 4118 */
        vuint32_t CPDMA_TX_PRI_MAP; /*   RW 32 0x0000 001C 0x4848 411C */
        vuint32_t CPDMA_RX_CH_MAP; /*   RW 32 0x0000 0020 0x4848 4120 */
        vuint32_t CPDMA_RX_CH_MAP_Padding[(0x4130 - 0x4120 - 0x4)/4];
        vuint32_t RX_DSCP_PRI_MAP0; /*   RW 32 0x0000 0030 0x4848 4130 */
        vuint32_t RX_DSCP_PRI_MAP1; /*   RW 32 0x0000 0034 0x4848 4134 */
        vuint32_t RX_DSCP_PRI_MAP2; /*   RW 32 0x0000 0038 0x4848 4138 */
        vuint32_t RX_DSCP_PRI_MAP3; /*   RW 32 0x0000 003C 0x4848 413C */
        vuint32_t RX_DSCP_PRI_MAP4; /*   RW 32 0x0000 0040 0x4848 4140 */
        vuint32_t RX_DSCP_PRI_MAP5; /*   RW 32 0x0000 0044 0x4848 4144 */
        vuint32_t RX_DSCP_PRI_MAP6; /*   RW 32 0x0000 0048 0x4848 4148 */
        vuint32_t RX_DSCP_PRI_MAP7; /*   RW 32 0x0000 004C 0x4848 414C */
        vuint32_t IDLE2LPI; /*  RW 32 0x0000 0050 0x4848 4150 */
        vuint32_t LPI2WAKE; /*  RW 32 0x0000 0054 0x4848 4154 */
    }PORT0;
    vuint32_t PORT0_Padding[(0x4200 - 0x4154 - 0x4)/4];
    struct{
        vuint32_t CONTROL; /* RW 32 0x0000 0100 0x4848 4200           */
        vuint32_t CONTROL_Padding[(0x4208 - 0x4200 - 0x4)/4];
        vuint32_t MAX_BLKS; /* RW 32 0x0000 0108 0x4848 4208          */
        vuint32_t BLK_CNT; /* RW 32 0x0000 010C 0x4848 420C           */
        vuint32_t TX_IN_CTL; /* RW 32 0x0000 0110 0x4848 4210         */
        vuint32_t PORT_VLAN; /* RW 32 0x0000 0114 0x4848 4214         */
        vuint32_t TX_PRI_MAP; /* RW 32 0x0000 0118 0x4848 4218        */
        vuint32_t TS_SEQ_MTYPE; /* RW 32 0x0000 011C 0x4848 421C      */
        vuint32_t SA_LO; /* RW 32 0x0000 0120 0x4848 4220             */
        vuint32_t SA_HI; /* RW 32 0x0000 0124 0x4848 4224             */
        vuint32_t SEND_PERCENT; /* RW 32 0x0000 0128 0x4848 4228      */
        vuint32_t SEND_PERCENT_Padding[(0x4230 - 0x4228 - 0x4)/4];
        vuint32_t RX_DSCP_PRI_MAP0; /* RW 32 0x0000 0130 0x4848 4230  */
        vuint32_t RX_DSCP_PRI_MAP1; /* RW 32 0x0000 0134 0x4848 4234  */
        vuint32_t RX_DSCP_PRI_MAP2; /* RW 32 0x0000 0138 0x4848 4238  */
        vuint32_t RX_DSCP_PRI_MAP3; /* RW 32 0x0000 013C 0x4848 423C  */
        vuint32_t RX_DSCP_PRI_MAP4; /* RW 32 0x0000 0140 0x4848 4240  */
        vuint32_t RX_DSCP_PRI_MAP5; /* RW 32 0x0000 0144 0x4848 4244  */
        vuint32_t RX_DSCP_PRI_MAP6; /* RW 32 0x0000 0148 0x4848 4248  */
        vuint32_t RX_DSCP_PRI_MAP7; /* RW 32 0x0000 014C 0x4848 424C  */
        vuint32_t IDLE2LPI; /* RW 32 0x0000 0150 0x4848 4250          */
        vuint32_t LPI2WAKE; /* RW 32 0x0000 0154 0x4848 4254          */
    }PORT1;
    vuint32_t PORT1_Padding[(0x4300 - 0x4254 - 0x4)/4];
    struct{
        vuint32_t CONTROL; /* RW 32 0x0000 0200 0x4848 4300                */
        vuint32_t CONTROL_Padding[(0x4308 - 0x4300 - 0x4)/4];
        vuint32_t MAX_BLKS; /* RW 32 0x0000 0208 0x4848 4308               */
        vuint32_t BLK_CNT; /* RW 32 0x0000 020C 0x4848 430C                */
        vuint32_t TX_IN_CTL; /* RW 32 0x0000 0210 0x4848 4310              */
        vuint32_t PORT_VLAN; /* RW 32 0x0000 0214 0x4848 4314              */
        vuint32_t TX_PRI_MAP; /* RW 32 0x0000 0218 0x4848 4318             */
        vuint32_t TS_SEQ_MTYPE; /* RW 32 0x0000 021C 0x4848 431C           */
        vuint32_t SA_LO; /* RW 32 0x0000 0220 0x4848 4320                  */
        vuint32_t SA_HI; /* RW 32 0x0000 0224 0x4848 4324                  */
        vuint32_t SEND_PERCENT; /* RW 32 0x0000 0228 0x4848 4328           */
        vuint32_t SEND_PERCENT_Padding[(0x4330 - 0x4328 - 0x4)/4];
        vuint32_t RX_DSCP_PRI_MAP0; /* RW 32 0x0000 0230 0x4848 4330       */
        vuint32_t RX_DSCP_PRI_MAP1; /* RW 32 0x0000 0234 0x4848 4334       */
        vuint32_t RX_DSCP_PRI_MAP2; /* RW 32 0x0000 0238 0x4848 4338       */
        vuint32_t RX_DSCP_PRI_MAP3; /* RW 32 0x0000 023C 0x4848 433C       */
        vuint32_t RX_DSCP_PRI_MAP4; /* RW 32 0x0000 0240 0x4848 4340       */
        vuint32_t RX_DSCP_PRI_MAP5; /* RW 32 0x0000 0244 0x4848 4344       */
        vuint32_t RX_DSCP_PRI_MAP6; /* RW 32 0x0000 0248 0x4848 4348       */
        vuint32_t RX_DSCP_PRI_MAP7; /* RW 32 0x0000 024C 0x4848 434C       */
        vuint32_t IDLE2LPI; /* RW 32 0x0000 0250 0x4848 4350               */
        vuint32_t LPI2WAKE; /* RW 32 0x0000 0254 0x4848 4354               */
    }PORT2;
    vuint32_t PORT2_Padding[(0x4800 - 0x4354 - 0x4)/4];
    struct{
        vuint32_t CPDMA_TX_IDVER; /* R 32 0x0000 0000 0x4848 4800                     */
        vuint32_t CPDMA_TX_CONTROL; /* RW 32 0x0000 0004 0x4848 4804                  */
        vuint32_t CPDMA_TX_TEARDOWN; /* RW 32 0x0000 0008 0x4848 4808                 */
        vuint32_t CPDMA_TX_TEARDOWN_Padding[(0x4810 - 0x4808 - 0x4)/4];
        vuint32_t CPDMA_RX_IDVER; /* R 32 0x0000 0010 0x4848 4810                     */
        vuint32_t CPDMA_RX_CONTROL; /* RW 32 0x0000 0014 0x4848 4814                  */
        vuint32_t CPDMA_RX_TEARDOWN; /* RW 32 0x0000 0018 0x4848 4818                 */
        vuint32_t CPDMA_SOFT_RESET; /* RW 32 0x0000 001C 0x4848 481C                  */
        vuint32_t CPDMA_DMACONTROL; /* RW 32 0x0000 0020 0x4848 4820                  */
        vuint32_t CPDMA_DMASTATUS; /* R 32 0x0000 0024 0x4848 4824                    */
        vuint32_t CPDMA_RX_BUFFER_OFFSET; /* RW 32 0x0000 0028 0x4848 4828            */
        vuint32_t CPDMA_EMCONTROL; /* RW 32 0x0000 002C 0x4848 482C                   */
        vuint32_t CPDMA_TX_PRI0_RATE; /* RW 32 0x0000 0030 0x4848 4830                */
        vuint32_t CPDMA_TX_PRI1_RATE; /* RW 32 0x0000 0034 0x4848 4834                */
        vuint32_t CPDMA_TX_PRI2_RATE; /* RW 32 0x0000 0038 0x4848 4838                */
        vuint32_t CPDMA_TX_PRI3_RATE; /* RW 32 0x0000 003C 0x4848 483C                */
        vuint32_t CPDMA_TX_PRI4_RATE; /* RW 32 0x0000 0040 0x4848 4840                */
        vuint32_t CPDMA_TX_PRI5_RATE; /* RW 32 0x0000 0044 0x4848 4844                */
        vuint32_t CPDMA_TX_PRI6_RATE; /* RW 32 0x0000 0048 0x4848 4848                */
        vuint32_t CPDMA_TX_PRI7_RATE; /* RW 32 0x0000 004C 0x4848 484C                */
        vuint32_t CPDMA_TX_PRI7_RATE_Padding[(0x4880 - 0x484C - 0x4)/4];
        vuint32_t CPDMA_TX_INTSTAT_RAW; /* R 32 0x0000 0080 0x4848 4880               */
        vuint32_t CPDMA_TX_INTSTAT_MASKED; /* R 32 0x0000 0084 0x4848 4884            */
        vuint32_t CPDMA_TX_INTMASK_SET; /* W 32 0x0000 0088 0x4848 4888               */
        vuint32_t CPDMA_TX_INTMASK_CLEAR; /* W 32 0x0000 008C 0x4848 488C             */
        vuint32_t CPDMA_IN_VECTOR; /* R 32 0x0000 0090 0x4848 4890                    */
        vuint32_t CPDMA_EOI_VECTOR; /* RW 32 0x0000 0094 0x4848 4894                  */
        vuint32_t CPDMA_EOI_VECTOR_Padding[(0x48A0 - 0x4894 - 0x4)/4];
        vuint32_t CPDMA_RX_INTSTAT_RAW; /* R 32 0x0000 00A0 0x4848 48A0               */
        vuint32_t CPDMA_RX_INTSTAT_MASKED; /* R 32 0x0000 00A4 0x4848 48A4            */
        vuint32_t CPDMA_RX_INTMASK_SET; /* RW 32 0x0000 00A8 0x4848 48A8              */
        vuint32_t CPDMA_RX_INTMASK_CLEAR; /* RW 32 0x0000 00AC 0x4848 48AC            */
        vuint32_t CPDMA_DMA_INTSTAT_RAW; /* R 32 0x0000 00B0 0x4848 48B0              */
        vuint32_t CPDMA_DMA_INTSTAT_MASKED; /* R 32 0x0000 00B4 0x4848 48B4           */
        vuint32_t CPDMA_DMA_INTMASK_SET; /* W 32 0x0000 00B8 0x4848 48B8              */
        vuint32_t CPDMA_DMA_INTMASK_CLEAR; /* RW 32 0x0000 00BC 0x4848 48BC           */
        vuint32_t CPDMA_RX0_PENDTHRESH; /* RW 32 0x0000 00C0 0x4848 48C0              */
        vuint32_t CPDMA_RX1_PENDTHRESH; /* RW 32 0x0000 00C4 0x4848 48C4              */
        vuint32_t CPDMA_RX2_PENDTHRESH; /* RW 32 0x0000 00C8 0x4848 48C8              */
        vuint32_t CPDMA_RX3_PENDTHRESH; /* RW 32 0x0000 00CC 0x4848 48CC              */
        vuint32_t CPDMA_RX4_PENDTHRESH; /* RW 32 0x0000 00D0 0x4848 48D0              */
        vuint32_t CPDMA_RX5_PENDTHRESH; /* RW 32 0x0000 00D4 0x4848 48D4              */
        vuint32_t CPDMA_RX6_PENDTHRESH; /* RW 32 0x0000 00D8 0x4848 48D8              */
        vuint32_t CPDMA_RX7_PENDTHRESH; /* RW 32 0x0000 00DC 0x4848 48DC              */
        vuint32_t CPDMA_RX0_FREEBUFFER; /* W 32 0x0000 00E0 0x4848 48E0               */
        vuint32_t CPDMA_RX1_FREEBUFFER; /* W 32 0x0000 00E4 0x4848 48E4               */
        vuint32_t CPDMA_RX2_FREEBUFFER; /* W 32 0x0000 00E8 0x4848 48E8               */
        vuint32_t CPDMA_RX3_FREEBUFFER; /* W 32 0x0000 00EC 0x4848 48EC               */
        vuint32_t CPDMA_RX4_FREEBUFFER; /* W 32 0x0000 00F0 0x4848 48F0               */
        vuint32_t CPDMA_RX5_FREEBUFFER; /* W 32 0x0000 00F4 0x4848 48F4               */
        vuint32_t CPDMA_RX6_FREEBUFFER; /* W 32 0x0000 00F8 0x4848 48F8               */
        vuint32_t CPDMA_RX7_FREEBUFFER; /* W 32 0x0000 00FC 0x4848 48FC               */
    }CPDMA;
    vuint32_t CPDMA_Padding[(0x4A00 - 0x48FC - 0x4)/4];
    struct{
        vuint32_t TX0_HDP; /* RW 32 0x0000 0000 0x4848 4A00                           */
        vuint32_t TX1_HDP; /* RW 32 0x0000 0004 0x4848 4A04                           */
        vuint32_t TX2_HDP; /* RW 32 0x0000 0008 0x4848 4A08                           */
        vuint32_t TX3_HDP; /* RW 32 0x0000 000C 0x4848 4A0C                           */
        vuint32_t TX4_HDP; /* RW 32 0x0000 0010 0x4848 4A10                           */
        vuint32_t TX5_HDP; /* RW 32 0x0000 0014 0x4848 4A14                           */
        vuint32_t TX6_HDP; /* RW 32 0x0000 0018 0x4848 4A18                           */
        vuint32_t TX7_HDP; /* RW 32 0x0000 001C 0x4848 4A1C                           */
        vuint32_t RX0_HDP; /* RW 32 0x0000 0020 0x4848 4A20                           */
        vuint32_t RX1_HDP; /* RW 32 0x0000 0024 0x4848 4A24                           */
        vuint32_t RX2_HDP; /* RW 32 0x0000 0028 0x4848 4A28                           */
        vuint32_t RX3_HDP; /* RW 32 0x0000 002C 0x4848 4A2C                           */
        vuint32_t RX4_HDP; /* RW 32 0x0000 0030 0x4848 4A30                           */
        vuint32_t RX5_HDP; /* RW 32 0x0000 0034 0x4848 4A34                           */
        vuint32_t RX6_HDP; /* RW 32 0x0000 0038 0x4848 4A38                           */
        vuint32_t RX7_HDP; /* RW 32 0x0000 003C 0x4848 4A3C                           */
        vuint32_t TX0_CP; /* RW 32 0x0000 0040 0x4848 4A40                            */
        vuint32_t TX1_CP; /* RW 32 0x0000 0044 0x4848 4A44                            */
        vuint32_t TX2_CP; /* RW 32 0x0000 0048 0x4848 4A48                            */
        vuint32_t TX3_CP; /* RW 32 0x0000 004C 0x4848 4A4C                            */
        vuint32_t TX4_CP; /* RW 32 0x0000 0050 0x4848 4A50                            */
        vuint32_t TX5_CP; /* RW 32 0x0000 0054 0x4848 4A54                            */
        vuint32_t TX6_CP; /* RW 32 0x0000 0058 0x4848 4A58                            */
        vuint32_t TX7_CP; /* RW 32 0x0000 005C 0x4848 4A5C                            */
        vuint32_t RX0_CP; /* RW 32 0x0000 0060 0x4848 4A60                            */
        vuint32_t RX1_CP; /* RW 32 0x0000 0064 0x4848 4A64                            */
        vuint32_t RX2_CP; /* RW 32 0x0000 0068 0x4848 4A68                            */
        vuint32_t RX3_CP; /* RW 32 0x0000 006C 0x4848 4A6C                            */
        vuint32_t RX4_CP; /* RW 32 0x0000 0070 0x4848 4A70                            */
        vuint32_t RX5_CP; /* RW 32 0x0000 0074 0x4848 4A74                            */
        vuint32_t RX6_CP; /* RW 32 0x0000 0078 0x4848 4A78                            */
        vuint32_t RX7_CP; /* RW 32 0x0000 007C 0x4848 4A7C                            */
    }STATERAM;
    vuint32_t STATERAM_Padding[(0x4C00 - 0x4A7C - 0x4)/4];
    struct{
        vuint32_t CPTS_IDVER; /* R 32 0x0000 0000 0x4848 4C00                         */
        vuint32_t CPTS_CONTROL; /* RW 32 0x0000 0004 0x4848 4C04                      */
        vuint32_t CPTS_CONTROL_Padding[(0x4C0C - 0x4C04 - 0x4)/4];
        vuint32_t CPTS_TS_PUSH; /* W 32 0x0000 000C 0x4848 4C0C                       */
        vuint32_t CPTS_TS_LOAD_VAL; /* RW 32 0x0000 0010 0x4848 4C10                  */
        vuint32_t CPTS_TS_LOAD_EN; /* W 32 0x0000 0014 0x4848 4C14                    */
        vuint32_t CPTS_TS_LOAD_EN_Padding[(0x4C20 - 0x4C14 - 0x4)/4];
        vuint32_t CPTS_INTSTAT_RAW; /* RW 32 0x0000 0020 0x4848 4C20                  */
        vuint32_t CPTS_INTSTAT_MASKED; /* R 32 0x0000 0024 0x4848 4C24                */
        vuint32_t CPTS_INT_ENABLE; /* RW 32 0x0000 0028 0x4848 4C28                   */
        vuint32_t CPTS_INT_ENABLE_Padding[(0x4C30 - 0x4C28 - 0x4)/4];
        vuint32_t CPTS_EVENT_POP; /* W 32 0x0000 0030 0x4848 4C30                     */
        vuint32_t CPTS_EVENT_LOW; /* R 32 0x0000 0034 0x4848 4C34                     */
        vuint32_t CPTS_EVENT_HIGH; /* R 32 0x0000 0038 0x4848 4C38                    */
    }CPTS;
    vuint32_t CPTS_Padding[(0x4D00 - 0x4C38 - 0x4)/4];
    struct{
        vuint32_t ALE_IDVER; /* R 32 0x0000 0000 0x4848 4D00                          */
        vuint32_t ALE_IDVER_Padding[(0x4D08 - 0x4D00 - 0x4)/4];
        vuint32_t ALE_CONTROL; /* RW 32 0x0000 0008 0x4848 4D08                       */
        vuint32_t ALE_CONTROL_Padding[(0x4D10 - 0x4D08 - 0x4)/4];
        vuint32_t ALE_PRESCALE; /* RW 32 0x0000 0010 0x4848 4D10                      */
        vuint32_t ALE_PRESCALE_Padding[(0x4D18 - 0x4D10 - 0x4)/4];
        vuint32_t ALE_UNKNOWN_VLAN; /* RW 32 0x0000 0018 0x4848 4D18                  */
        vuint32_t ALE_UNKNOWN_VLAN_Padding[(0x4D20 - 0x4D18 - 0x4)/4];
        vuint32_t ALE_TBLCTL; /* RW 32 0x0000 0020 0x4848 4D20                        */
        vuint32_t ALE_TBLCTL_Padding[(0x4D34 - 0x4D20 - 0x4)/4];
        vuint32_t ALE_TBLW2; /* RW 32 0x0000 0034 0x4848 4D34                         */
        vuint32_t ALE_TBLW1; /* RW 32 0x0000 0038 0x4848 4D38                         */
        vuint32_t ALE_TBLW0; /* RW 32 0x0000 003C 0x4848 4D3C                         */
        vuint32_t ALE_PORTCTL0; /* RW 32 0x0000 0040 0x4848 4D40                      */
        vuint32_t ALE_PORTCTL1; /* RW 32 0x0000 0044 0x4848 4D44                      */
        vuint32_t ALE_PORTCTL2; /* RW 32 0x0000 0048 0x4848 4D48                      */
        vuint32_t ALE_PORTCTL3; /* RW 32 0x0000 004C 0x4848 4D4C                      */
        vuint32_t ALE_PORTCTL4; /* RW 32 0x0000 0050 0x4848 4D50                      */
        vuint32_t ALE_PORTCTL5; /* RW 32 0x0000 0054 0x4848 4D54                      */
    }ALE;
    vuint32_t ALE_Padding[(0x4D80 - 0x4D54 - 0x4)/4];
    struct{
        vuint32_t SL_IDVER; /* R 32 0x0000 0000 0x4848 4D80 0x4848 4DC0               */
        vuint32_t SL_MACCONTROL; /* RW 32 0x0000 0004 0x4848 4D84 0x4848 4DC4         */
        vuint32_t SL_MACSTATUS; /* R 32 0x0000 0008 0x4848 4D88 0x4848 4DC8           */
        vuint32_t SL_SOFT_RESET; /* RW 32 0x0000 000C 0x4848 4D8C 0x4848 4DCC         */
        vuint32_t SL_RX_MAXLEN; /* RW 32 0x0000 0010 0x4848 4D90 0x4848 4DD0          */
        vuint32_t SL_BOFFTEST; /* RW 32 0x0000 0014 0x4848 4D94 0x4848 4DD4           */
        vuint32_t SL_RX_PAUSE; /* R 32 0x0000 0018 0x4848 4D98 0x4848 4DD8            */
        vuint32_t SL_TX_PAUSE; /* R 32 0x0000 001C 0x4848 4D9C 0x4848 4DDC            */
        vuint32_t SL_EMCONTROL; /* RW 32 0x0000 0020 0x4848 4DA0 0x4848 4DE0          */
        vuint32_t SL_RX_PRI_MAP; /* RW 32 0x0000 0024 0x4848 4DA4 0x4848 4DE4         */
        vuint32_t SL_TX_GAP; /* RW 32 0x0000 0028 0x4848 4DA8 0x4848 4DE8             */
    }SL1;
    vuint32_t SL1_Padding[(0x4DC0 - 0x4DA8 - 0x4)/4];
    struct{
        vuint32_t SL_IDVER; /* R 32 0x0000 0000 0x4848 4D80 0x4848 4DC0               */
        vuint32_t SL_MACCONTROL; /* RW 32 0x0000 0004 0x4848 4D84 0x4848 4DC4         */
        vuint32_t SL_MACSTATUS; /* R 32 0x0000 0008 0x4848 4D88 0x4848 4DC8           */
        vuint32_t SL_SOFT_RESET; /* RW 32 0x0000 000C 0x4848 4D8C 0x4848 4DCC         */
        vuint32_t SL_RX_MAXLEN; /* RW 32 0x0000 0010 0x4848 4D90 0x4848 4DD0          */
        vuint32_t SL_BOFFTEST; /* RW 32 0x0000 0014 0x4848 4D94 0x4848 4DD4           */
        vuint32_t SL_RX_PAUSE; /* R 32 0x0000 0018 0x4848 4D98 0x4848 4DD8            */
        vuint32_t SL_TX_PAUSE; /* R 32 0x0000 001C 0x4848 4D9C 0x4848 4DDC            */
        vuint32_t SL_EMCONTROL; /* RW 32 0x0000 0020 0x4848 4DA0 0x4848 4DE0          */
        vuint32_t SL_RX_PRI_MAP; /* RW 32 0x0000 0024 0x4848 4DA4 0x4848 4DE4         */
        vuint32_t SL_TX_GAP; /* RW 32 0x0000 0028 0x4848 4DA8 0x4848 4DE8             */
    }SL2;
    vuint32_t SL2_Padding[(0x5000 - 0x4DE8 - 0x4)/4];
    struct{
        vuint32_t MDIO_VER; /* RW 32 0x0000 0000 0x4848 5000                          */
        vuint32_t MDIO_CONTROL; /* RW 32 0x0000 0004 0x4848 5004                      */
        vuint32_t MDIO_ALIVE; /* RW 32 0x0000 0008 0x4848 5008                        */
        vuint32_t MDIO_LINK; /* R 32 0x0000 000C 0x4848 500C                          */
        vuint32_t MDIO_LINKINTRAW; /* RW 32 0x0000 0010 0x4848 5010                   */
        vuint32_t MDIO_LINKINTMASKED; /* RW 32 0x0000 0014 0x4848 5014                */
        vuint32_t MDIO_LINKINTMASKED_Padding[(0x5020 - 0x5014 - 0x4)/4];
        vuint32_t MDIO_USERINTRAW; /* RW 32 0x0000 0020 0x4848 5020                   */
        vuint32_t MDIO_USERINTMASKED; /* RW 32 0x0000 0024 0x4848 5024                */
        vuint32_t MDIO_USERINTMASKSET; /* RW 32 0x0000 0028 0x4848 5028               */
        vuint32_t MDIO_USERINTMASKCLR; /* RW 32 0x0000 002C 0x4848 502C               */
        vuint32_t MDIO_USERINTMASKCLR_Padding[(0x5080 - 0x502C - 0x4)/4];
        vuint32_t MDIO_USERACCESS0; /* RW 32 0x0000 0080 0x4848 5080                  */
        vuint32_t MDIO_USERPHYSEL0; /* RW 32 0x0000 0084 0x4848 5084                  */
        vuint32_t MDIO_USERACCESS1; /* RW 32 0x0000 0088 0x4848 5088                  */
        vuint32_t MDIO_USERPHYSEL1; /* RW 32 0x0000 008C 0x4848 508C                  */
    }MDIO;
    vuint32_t MDIO_Padding[(0x5200 - 0x508C - 0x4)/4];
    struct{
        vuint32_t WR_IDVER; /* R 32 0x0000 0000 0x4848 5200                           */
        vuint32_t WR_SOFT_RESET; /* RW 32 0x0000 0004 0x4848 5204                     */
        vuint32_t WR_CONTROL; /* RW 32 0x0000 0008 0x4848 5208                        */
        vuint32_t WR_INT_CONTROL; /* RW 32 0x0000 000C 0x4848 520C                    */
        vuint32_t WR_C0_RX_THRESH_EN; /* RW 32 0x0000 0010 0x4848 5210                */
        vuint32_t WR_C0_RX_EN; /* RW 32 0x0000 0014 0x4848 5214                       */
        vuint32_t WR_C0_TX_EN; /* RW 32 0x0000 0018 0x4848 5218                       */
        vuint32_t WR_C0_MISC_EN; /* RW 32 0x0000 001C 0x4848 521C                     */
        vuint32_t WR_C0_MISC_EN_Padding[(0x5240 - 0x521C - 0x4)/4];
        vuint32_t WR_C0_RX_THRESH_STAT; /* R 32 0x0000 0040 0x4848 5240               */
        vuint32_t WR_C0_RX_STAT; /* R 32 0x0000 0044 0x4848 5244                      */
        vuint32_t WR_C0_TX_STAT; /* R 32 0x0000 0048 0x4848 5248                      */
        vuint32_t WR_C0_MISC_STAT; /* R 32 0x0000 004C 0x4848 524C                    */
        vuint32_t WR_C0_MISC_STAT_Padding[(0x5270 - 0x524C - 0x4)/4];
        vuint32_t WR_C0_RX_IMAX; /* RW 32 0x0000 0070 0x4848 5270                     */
        vuint32_t WR_C0_TX_IMAX; /* RW 32 0x0000 0074 0x4848 5274                     */
        vuint32_t WR_C0_TX_IMAX_Padding[(0x5288 - 0x5274 - 0x4)/4];
        vuint32_t WR_RGMII_CTL; /* R 32 0x0000 0088 0x4848 5288                       */
    }WR;
    vuint32_t WR_Padding[(0x6000 - 0x5288 - 0x4)/4];
    vuint8_t *CPPI_RAM; /* 0x4848 6000 8 KiB */
} __attribute__((packed));

/*lint -restore*/

typedef enum{
    ALE_FREE_ENTRY,
    ALE_ADRS_ENTRY,
    ALE_VLAN_ENTRY,
    ALE_VLAN_ADRS_ENTRY
}Eth_AleTablEntryType;

typedef enum{
    ALE_UNI_ADRS_NOT_AGEABLE,
    ALE_UNI_ADRS_AGEABLE_NOT_TOUCHED,
    ALE_UNI_ADRS_OUI_NOT_AGEABLE,
    ALE_UNI_ADRS_AGEABLE_TOUCHED
}Eth_AleTablUnicastType;

typedef enum{
    FIFO_NORMAL_PRIO,
    FIFO_DUAL_MAC,
    FIFO_RATE_LIMIT
}Eth_FifoPrioType;


typedef volatile struct GmacSw_reg GmacSw_HwRegType; /* HW register type */

/* Abstract Interfacing, separate header file is not used for this */
#if defined(CFG_ETH_HW_SHARE)

typedef struct _Eth_HwPvtConfig
{
	void (*vConfigureTxQueue)(uint8 EthHwPort,uint8 Queue);
	void (*vConfigureRxQueue)(uint8 EthHwPort,uint8 Queue, uint8 DmaCh);
	void (*vConfigureControllerExtra)(uint8 EthHwPort);
	uint16 (*vGetConfiguredVid)(uint8 EthHwPort);
} Eth_HwPvtConfig;
extern const Eth_HwPvtConfig EthHwPvtConfig;
#endif

#endif /* ETH_JACINTO_H_ */
