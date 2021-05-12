#include "MgmtGUIDs.h"


///////////////////////////////////////////////////////////////////////////////
//
// GUIDs for built-in layers.
//
///////////////////////////////////////////////////////////////////////////////
#pragma region layers
static fwpm_layer_desc_t fwpm_layer_desc_list[] = {
    {
        FWPM_LAYER_ALE_AUTH_CONNECT_V4,
        "FWPM_LAYER_ALE_AUTH_CONNECT_V4",
        "This filtering layer allows for authorizing connect requests for outgoing TCP connections, as well as authorizing outgoing non-TCP traffic based on the first packet sent."
    },
    {
        FWPM_LAYER_ALE_AUTH_CONNECT_V4_DISCARD,
        "FWPM_LAYER_ALE_AUTH_CONNECT_V4_DISCARD",
        "This filtering layer allows for inspecting connect requests for outgoing TCP connections that have been discarded, as well as inspecting authorizations for outgoing non-TCP traffic that have been discarded."
    },
	{
		FWPM_LAYER_ALE_FLOW_ESTABLISHED_V4,
		"FWPM_LAYER_ALE_FLOW_ESTABLISHED_V4",
		"This filtering layer allows for notification of when a TCP connection has been established, or when non-TCP traffic has been authorized."
	},
    {
        FWPM_LAYER_ALE_AUTH_CONNECT_V6,
        "FWPM_LAYER_ALE_AUTH_CONNECT_V6",
        "This filtering layer allows for authorizing connect requests for outgoing TCP connections, as well as authorizing outgoing non-TCP traffic based on the first packet sent."
    },
    {
        FWPM_LAYER_ALE_AUTH_CONNECT_V6_DISCARD,
        "FWPM_LAYER_ALE_AUTH_CONNECT_V4_DISCARD",
        "This filtering layer allows for inspecting connect requests for outgoing TCP connections that have been discarded, as well as inspecting authorizations for outgoing non-TCP traffic that have been discarded."
    },
    {
        FWPM_LAYER_ALE_AUTH_LISTEN_V4,
        "FWPM_LAYER_ALE_AUTH_LISTEN_V4",
        "This filtering layer allows for authorizing TCP listen requests."
    },
    {
        FWPM_LAYER_ALE_AUTH_LISTEN_V4_DISCARD,
        "FWPM_LAYER_ALE_AUTH_LISTEN_V4_DISCARD",
        "This filtering layer allows for inspecting TCP listen requests that have been discarded."
    },
	{
        FWPM_LAYER_ALE_AUTH_LISTEN_V6,
        "FWPM_LAYER_ALE_AUTH_LISTEN_V6",
        "This filtering layer allows for authorizing TCP listen requests."
    },
    {
        FWPM_LAYER_ALE_AUTH_LISTEN_V6_DISCARD,
        "FWPM_LAYER_ALE_AUTH_LISTEN_V6_DISCARD",
        "This filtering layer allows for inspecting TCP listen requests that have been discarded."
    },
    {
		FWPM_LAYER_ALE_AUTH_RECV_ACCEPT_V4,
		"FWPM_LAYER_ALE_AUTH_RECV_ACCEPT_V4",
        "This filtering layer allows for authorizing accept requests for incoming TCP connections, as well as authorizing incoming non-TCP traffic based on the first packet received."
    },
    {
        FWPM_LAYER_ALE_AUTH_RECV_ACCEPT_V4_DISCARD,
        "FWPM_LAYER_ALE_AUTH_RECV_ACCEPT_V4_DISCARD",
        "This filtering layer allows for inspecting accept requests for incoming TCP connections that have been discarded, as well as inspecting authorizations for incoming non-TCP traffic that have been discarded."
    },
    {
		FWPM_LAYER_ALE_AUTH_RECV_ACCEPT_V6,
		"FWPM_LAYER_ALE_AUTH_RECV_ACCEPT_V6",
        "This filtering layer allows for authorizing accept requests for incoming TCP connections, as well as authorizing incoming non-TCP traffic based on the first packet received."
    },
    {
        FWPM_LAYER_ALE_AUTH_RECV_ACCEPT_V6_DISCARD,
        "FWPM_LAYER_ALE_AUTH_RECV_ACCEPT_V6_DISCARD",
        "This filtering layer allows for inspecting accept requests for incoming TCP connections that have been discarded, as well as inspecting authorizations for incoming non-TCP traffic that have been discarded."
    },
    {
        FWPM_LAYER_ALE_BIND_REDIRECT_V4,
        "FWPM_LAYER_ALE_BIND_REDIRECT_V4",
        "This filtering layer allows for modification of bind() and connect() calls and selection of host routes."
    },
    {
        FWPM_LAYER_ALE_BIND_REDIRECT_V6,
        "FWPM_LAYER_ALE_BIND_REDIRECT_V4",
        "This filtering layer allows for modification of bind() and connect() calls and selection of host routes."
    },
    {
		FWPM_LAYER_ALE_CONNECT_REDIRECT_V4,
		"FWPM_LAYER_ALE_CONNECT_REDIRECT_V4",
        "This filtering layer allows for modification of addresses and ports at the bind_redirect layer.  For TCP, the local addressand /or local port as well as the remote address and /or remote port can be modified.  For UDP, the local addressand /or local port can be modified."
    },
    {
		FWPM_LAYER_ALE_CONNECT_REDIRECT_V6,
		"FWPM_LAYER_ALE_CONNECT_REDIRECT_V6",
        "This filtering layer allows for modification of addresses and ports at the bind_redirect layer.  For TCP, the local addressand /or local port as well as the remote address and /or remote port can be modified.  For UDP, the local addressand /or local port can be modified."
    },
    {
        FWPM_LAYER_ALE_ENDPOINT_CLOSURE_V4,
        "FWPM_LAYER_ALE_ENDPOINT_CLOSURE_V4",
        ""
    },
    {
        FWPM_LAYER_ALE_ENDPOINT_CLOSURE_V6,
        "FWPM_LAYER_ALE_ENDPOINT_CLOSURE_V6",
        ""
    },
    {
        FWPM_LAYER_ALE_RESOURCE_ASSIGNMENT_V4,
        "FWPM_LAYER_ALE_RESOURCE_ASSIGNMENT_V4",
        "This filtering layer allows for authorizing transport port assignments, bind requests, promiscuous mode requests, and raw mode requests."
    },
    {
        FWPM_LAYER_ALE_RESOURCE_ASSIGNMENT_V4_DISCARD,
        "FWPM_LAYER_ALE_RESOURCE_ASSIGNMENT_V4_DISCARD",
        "This filtering layer allows for inspecting the following discarded items: transport port assignments, bind requests, promiscuous mode requests, and raw mode requests."
    },
    {
        FWPM_LAYER_ALE_RESOURCE_ASSIGNMENT_V6,
        "FWPM_LAYER_ALE_RESOURCE_ASSIGNMENT_V6",
        "This filtering layer allows for authorizing transport port assignments, bind requests, promiscuous mode requests, and raw mode requests."
    },
    {
        FWPM_LAYER_ALE_RESOURCE_ASSIGNMENT_V6_DISCARD,
        "FWPM_LAYER_ALE_RESOURCE_ASSIGNMENT_V6_DISCARD",
        "This filtering layer allows for inspecting the following discarded items: transport port assignments, bind requests, promiscuous mode requests, and raw mode requests."
    },
    {
        FWPM_LAYER_ALE_RESOURCE_RELEASE_V4,
        "FWPM_LAYER_ALE_RESOURCE_RELEASE_V4",
        "This filtering layer allows for resources previously allocated to be released"
    },
    {
        FWPM_LAYER_ALE_RESOURCE_RELEASE_V6,
        "FWPM_LAYER_ALE_RESOURCE_RELEASE_V6",
        "This filtering layer allows for resources previously allocated to be released"
    },
    {
        FWPM_LAYER_DATAGRAM_DATA_V4,
        "FWPM_LAYER_DATAGRAM_DATA_V4",
        "This filtering layer is located in the datagram data path. This layer allows for inspecting network data on a per datagram basis. At the datagram layer, the network data is bidirectional."
    },
    {
        FWPM_LAYER_DATAGRAM_DATA_V4_DISCARD,
        "FWPM_LAYER_DATAGRAM_DATA_V4_DISCARD",
        "This filtering layer is located in the datagram data path for inspecting any datagrams that have been discarded."
    },
    {
        FWPM_LAYER_DATAGRAM_DATA_V6,
        "FWPM_LAYER_DATAGRAM_DATA_V6",
        "This filtering layer is located in the datagram data path. This layer allows for inspecting network data on a per datagram basis. At the datagram layer, the network data is bidirectional."
    },
    {
        FWPM_LAYER_DATAGRAM_DATA_V6_DISCARD,
        "FWPM_LAYER_DATAGRAM_DATA_V6_DISCARD",
        "This filtering layer is located in the datagram data path for inspecting any datagrams that have been discarded."
    },
    {
        FWPM_LAYER_EGRESS_VSWITCH_ETHERNET,
        "FWPM_LAYER_EGRESS_VSWITCH_ETHERNET",
        "This filtering layer is located in the vSwitch egress path just after the MAC header has been parsed, but before any MAC header processing takes place."
    },
    {
        FWPM_LAYER_EGRESS_VSWITCH_TRANSPORT_V4,
        "FWPM_LAYER_EGRESS_VSWITCH_TRANSPORT_V4",
        "This filtering layer is located in the vSwitch egress path just after the MAC header has been parsed, but before any MAC header processing takes place. This layer allows for TRANSPORT level filtering conditions to aid in filtering traffic.  If a vSwitchPort is in PVLAN or trunk mode, filters at this layer will be bypassed, letting the traffic flow through without any filtering. If IPv4 is uninstalled in the host, filters in this layer will cause packets to be dropped."
    },
    {
        FWPM_LAYER_EGRESS_VSWITCH_TRANSPORT_V6,
        "FWPM_LAYER_EGRESS_VSWITCH_TRANSPORT_V6",
        "This filtering layer is located in the vSwitch egress path just after the MAC header has been parsed, but before any MAC header processing takes place. This layer allows for TRANSPORT level filtering conditions to aid in filtering traffic.  If a vSwitchPort is in PVLAN or trunk mode, filters at this layer will be bypassed, letting the traffic flow through without any filtering. If IPv4 is uninstalled in the host, filters in this layer will cause packets to be dropped."
    },
    {
        FWPM_LAYER_IKEEXT_V4,
        "FWPM_LAYER_IKEEXT_V4",
        "This filtering layer allows the IKE and authenticated IP modules to look up main-mode policy information when negotiating main-mode security associations. This is a user-mode filtering layer."
    },
    {
        FWPM_LAYER_IKEEXT_V6,
        "FWPM_LAYER_IKEEXT_V6",
        "This filtering layer allows the IKE and authenticated IP modules to look up main-mode policy information when negotiating main-mode security associations. This is a user-mode filtering layer."
    },
    {
        FWPM_LAYER_INBOUND_ICMP_ERROR_V4,
        "FWPM_LAYER_INBOUND_ICMP_ERROR_V4",
        "This filtering layer is located in the receive path for inspecting received ICMP error messages for the transport protocol."
    },
    {
        FWPM_LAYER_INBOUND_ICMP_ERROR_V4_DISCARD,
        "FWPM_LAYER_INBOUND_ICMP_ERROR_V4_DISCARD",
        "This filtering layer is located in the receive path for inspecting received ICMP error messages that have been discarded."
    },
    {
        FWPM_LAYER_INBOUND_ICMP_ERROR_V6,
        "FWPM_LAYER_INBOUND_ICMP_ERROR_V6",
        "This filtering layer is located in the receive path for inspecting received ICMP error messages for the transport protocol."
    },
    {
        FWPM_LAYER_INBOUND_ICMP_ERROR_V6_DISCARD,
        "FWPM_LAYER_INBOUND_ICMP_ERROR_V6_DISCARD",
        "This filtering layer is located in the receive path for inspecting received ICMP error messages that have been discarded."
    },
    {
        FWPM_LAYER_INBOUND_IPPACKET_V4,
        "FWPM_LAYER_INBOUND_IPPACKET_V4",
        "This filtering layer is located in the receive path just after the IP header of a received packet has been parsed but before any IP header processing takes place. No IPsec decryption or reassembly has occurred."
    },
    {
        FWPM_LAYER_INBOUND_IPPACKET_V4_DISCARD,
        "FWPM_LAYER_INBOUND_IPPACKET_V4_DISCARD",
        "This filtering layer is located in the receive path for inspecting any received packets that have been discarded at the network layer."
    },
    {
        FWPM_LAYER_INBOUND_IPPACKET_V6,
        "FWPM_LAYER_INBOUND_IPPACKET_V6",
        "This filtering layer is located in the receive path just after the IP header of a received packet has been parsed but before any IP header processing takes place. No IPsec decryption or reassembly has occurred."
    },
    {
        FWPM_LAYER_INBOUND_IPPACKET_V6_DISCARD,
        "FWPM_LAYER_INBOUND_IPPACKET_V6_DISCARD",
        "This filtering layer is located in the receive path for inspecting any received packets that have been discarded at the network layer."
    },
    {
        FWPM_LAYER_INBOUND_TRANSPORT_V4,
        "FWPM_LAYER_INBOUND_TRANSPORT_V4",
        "This filtering layer is located in the receive path just after a received packet's transport header has been parsed by the network stack at the transport layer, but before any transport layer processing takes place."
    },
    {
        FWPM_LAYER_INBOUND_TRANSPORT_V4_DISCARD,
        "FWPM_LAYER_INBOUND_TRANSPORT_V4_DISCARD",
        "This filtering layer is located in the receive path for inspecting any received packets that have been discarded at the transport layer."
    },
    {
        FWPM_LAYER_INBOUND_TRANSPORT_V6,
        "FWPM_LAYER_INBOUND_TRANSPORT_V6",
        "This filtering layer is located in the receive path just after a received packet's transport header has been parsed by the network stack at the transport layer, but before any transport layer processing takes place."
    },
    {
        FWPM_LAYER_INBOUND_TRANSPORT_V6_DISCARD,
        "FWPM_LAYER_INBOUND_TRANSPORT_V6_DISCARD",
        "This filtering layer is located in the receive path for inspecting any received packets that have been discarded at the transport layer."
    },
    {
        FWPM_LAYER_INGRESS_VSWITCH_ETHERNET,
        "FWPM_LAYER_INGRESS_VSWITCH_ETHERNET",
        "This filtering layer is located in the vSwitch ingress path just after the MAC header has been parsed, but before any MAC header processing takes place."
    },
    {
        FWPM_LAYER_INGRESS_VSWITCH_TRANSPORT_V4,
        "FWPM_LAYER_INGRESS_VSWITCH_TRANSPORT_V4",
        "This filtering layer is located in the vSwitch ingress path just after the MAC header has been parsed, but before any MAC header processing takes place. This layer allows for TRANSPORT level filtering conditions to aid in filtering traffic.  If a vSwitchPort is in PVLAN or trunk mode, filters at this layer will be bypassed, letting the traffic flow through without any filtering. If IPv4 is uninstalled in the host, filters in this layer will cause packets to be dropped"
    },
    {
        FWPM_LAYER_INGRESS_VSWITCH_TRANSPORT_V6,
        "FWPM_LAYER_INGRESS_VSWITCH_TRANSPORT_V6",
        "This filtering layer is located in the vSwitch ingress path just after the MAC header has been parsed, but before any MAC header processing takes place. This layer allows for TRANSPORT level filtering conditions to aid in filtering traffic.  If a vSwitchPort is in PVLAN or trunk mode, filters at this layer will be bypassed, letting the traffic flow through without any filtering. If IPv4 is uninstalled in the host, filters in this layer will cause packets to be dropped"
    },
    {
        FWPM_LAYER_IPSEC_KM_DEMUX_V4,
        "FWPM_LAYER_IPSEC_KM_DEMUX_V4",
        "This filtering layer is used to determine which keying modules are invoked when the local system is the initiator. This is a user-mode filtering layer."
    },
    {
        FWPM_LAYER_IPSEC_KM_DEMUX_V6,
        "FWPM_LAYER_IPSEC_KM_DEMUX_V6",
        "This filtering layer is used to determine which keying modules are invoked when the local system is the initiator. This is a user-mode filtering layer."
    },
    {
        FWPM_LAYER_IPSEC_V4,
        "FWPM_LAYER_IPSEC_V4",
        "This filtering layer allows the keying module to look up quick-mode policy information when negotiating quick-mode security associations. This is a user-mode filtering layer."
    },
    {
        FWPM_LAYER_IPSEC_V6,
        "FWPM_LAYER_IPSEC_V6",
        "This filtering layer allows the keying module to look up quick-mode policy information when negotiating quick-mode security associations. This is a user-mode filtering layer."
    },
    {
        FWPM_LAYER_KM_AUTHORIZATION,
        "FWPM_LAYER_KM_AUTHORIZATION",
        "This filtering layer allows for authorizing security association establishment."
    },
    {
        FWPM_LAYER_NAME_RESOLUTION_CACHE_V4,
        "FWPM_LAYER_NAME_RESOLUTION_CACHE_V4",
        "This filtering layer allows for querying the names recently resolved by the system."
    },
    {
        FWPM_LAYER_NAME_RESOLUTION_CACHE_V6,
        "FWPM_LAYER_NAME_RESOLUTION_CACHE_V6",
        "This filtering layer allows for querying the names recently resolved by the system."
    },
    {
        FWPM_LAYER_OUTBOUND_ICMP_ERROR_V4,
        "FWPM_LAYER_OUTBOUND_ICMP_ERROR_V4",
        "This filtering layer is located in the send path for inspecting received ICMP error messages for the transport protocol."
    },
    {
        FWPM_LAYER_OUTBOUND_ICMP_ERROR_V4_DISCARD,
        "FWPM_LAYER_OUTBOUND_ICMP_ERROR_V4_DISCARD",
        "This filtering layer is located in the send path for inspecting received ICMP error messages that have been discarded."
    },
    {
        FWPM_LAYER_OUTBOUND_ICMP_ERROR_V6,
        "FWPM_LAYER_OUTBOUND_ICMP_ERROR_V6",
        "This filtering layer is located in the send path for inspecting received ICMP error messages for the transport protocol."
    },
    {
        FWPM_LAYER_OUTBOUND_ICMP_ERROR_V6_DISCARD,
        "FWPM_LAYER_OUTBOUND_ICMP_ERROR_V6_DISCARD",
        "This filtering layer is located in the send path for inspecting received ICMP error messages that have been discarded."
    },
    {
        FWPM_LAYER_OUTBOUND_IPPACKET_V4,
        "FWPM_LAYER_OUTBOUND_IPPACKET_V4",
        "This filtering layer is located in the send path just before the sent packet is evaluated for fragmentation. All IP header processing is complete and all extension headers are in place. Any IPsec authentication and encryption has already occurred."
    },
    {
        FWPM_LAYER_OUTBOUND_IPPACKET_V4_DISCARD,
        "FWPM_LAYER_OUTBOUND_IPPACKET_V4_DISCARD",
        "This filtering layer is located in the send path for inspecting any sent packets that have been discarded at the network layer."
    },
    {
        FWPM_LAYER_OUTBOUND_IPPACKET_V6,
        "FWPM_LAYER_OUTBOUND_IPPACKET_V6",
        "This filtering layer is located in the send path just before the sent packet is evaluated for fragmentation. All IP header processing is complete and all extension headers are in place. Any IPsec authentication and encryption has already occurred."
    },
    {
        FWPM_LAYER_OUTBOUND_IPPACKET_V6_DISCARD,
        "FWPM_LAYER_OUTBOUND_IPPACKET_V6_DISCARD",
        "This filtering layer is located in the send path for inspecting any sent packets that have been discarded at the network layer."
    },
    {
        FWPM_LAYER_OUTBOUND_TRANSPORT_V4,
        "FWPM_LAYER_OUTBOUND_TRANSPORT_V4",
        "This filtering layer is located in the send path just after a sent packet has been passed to the network layer for processing but before any network layer processing takes place. This filtering layer is located at the top of the network layer instead of at the bottom of the transport layer so that any packets that are sent by third-party transports or as raw packets are filtered at this layer."
    },
    {
        FWPM_LAYER_OUTBOUND_TRANSPORT_V4_DISCARD,
        "FWPM_LAYER_OUTBOUND_TRANSPORT_V4_DISCARD",
        "This filtering layer is located in the send path for inspecting any sent packets that have been discarded at the transport layer."
    },
    {
        FWPM_LAYER_OUTBOUND_TRANSPORT_V6,
        "FWPM_LAYER_OUTBOUND_TRANSPORT_V6",
        "This filtering layer is located in the send path just after a sent packet has been passed to the network layer for processing but before any network layer processing takes place. This filtering layer is located at the top of the network layer instead of at the bottom of the transport layer so that any packets that are sent by third-party transports or as raw packets are filtered at this layer."
    },
    {
        FWPM_LAYER_OUTBOUND_TRANSPORT_V6_DISCARD,
        "FWPM_LAYER_OUTBOUND_TRANSPORT_V6_DISCARD",
        "This filtering layer is located in the send path for inspecting any sent packets that have been discarded at the transport layer."
    },
    {
        FWPM_LAYER_RPC_EPMAP,
        "FWPM_LAYER_RPC_EPMAP",
        "This filtering layer allows for inspecting the RPC data fields that are available in user mode during endpoint resolution. This is a user-mode filtering layer."
    },
    {
        FWPM_LAYER_RPC_EP_ADD,
        "FWPM_LAYER_RPC_EP_ADD",
        "This filtering layer allows for inspecting the RPC data fields that are available in user mode when a new endpoint is added. This is a user-mode filtering layer."
    },
    {
        FWPM_LAYER_RPC_PROXY_CONN,
        "FWPM_LAYER_RPC_PROXY_CONN",
        "This filtering layer allows for inspecting the RpcProxy connection requests. This is a user-mode filtering layer."
    },
    {
        FWPM_LAYER_RPC_UM,
        "FWPM_LAYER_RPC_UM",
        "This filtering layer allows for inspecting the RPC data fields that are available in user mode. This is a user-mode filtering layer."
    },
    {
        FWPM_LAYER_STREAM_PACKET_V4,
        "FWPM_LAYER_STREAM_PACKET_V4",
        "This filtering layer allows for inspection of TCP packets including handshake and flow control exchanges."
    },
    {
        FWPM_LAYER_STREAM_PACKET_V6,
        "FWPM_LAYER_STREAM_PACKET_V6",
        "This filtering layer allows for inspection of TCP packets including handshake and flow control exchanges."
    },
    {
        FWPM_LAYER_STREAM_V4,
        "FWPM_LAYER_STREAM_V4",
        "This filtering layer is located in the stream data path. This layer allows for inspecting network data on a per stream basis. At the stream layer, the network data is bidirectional."
    },
    {
        FWPM_LAYER_STREAM_V4_DISCARD,
        "FWPM_LAYER_STREAM_V4_DISCARD",
        "This filtering layer is located in the stream data path for inspecting any stream data that has been discarded."
    },
    {
        FWPM_LAYER_STREAM_V6,
        "FWPM_LAYER_STREAM_V6",
        "This filtering layer is located in the stream data path. This layer allows for inspecting network data on a per stream basis. At the stream layer, the network data is bidirectional."
    },
    {
        FWPM_LAYER_STREAM_V6_DISCARD,
        "FWPM_LAYER_STREAM_V6_DISCARD",
        "This filtering layer is located in the stream data path for inspecting any stream data that has been discarded."
    },
};
#pragma endregion

///////////////////////////////////////////////////////////////////////////////
//
// GUIDs for built-in sublayers.
//
///////////////////////////////////////////////////////////////////////////////
#pragma region sublayers

static fwpm_sublayer_desc_t fwpm_sublayer_desc_list[] = {
    {
        // 758c84f4-fb48-4de9-9aeb-3ed9551ab1fd
        FWPM_SUBLAYER_RPC_AUDIT,
        "FWPM_SUBLAYER_RPC_AUDIT",
        "RPC audit filters are added to this sublayer. These filters audit RPC incoming calls as part of C2 and common criteria compliance."
    },
    {
        // 83f299ed-9ff4-4967-aff4-c309f4dab827
        FWPM_SUBLAYER_IPSEC_TUNNEL,
        "FWPM_SUBLAYER_IPSEC_TUNNEL",
        "IPsec tunnel filters are added to this sublayer."
    },
    {
        // eebecc03-ced4-4380-819a-2734397b2b74
        FWPM_SUBLAYER_UNIVERSAL,
        "FWPM_SUBLAYER_UNIVERSAL",
        "This sublayer hosts all filters that are not assigned to any of the other sublayers."
    },
    {
        // 1b75c0ce-ff60-4711-a70f-b4958cc3b2d0
        FWPM_SUBLAYER_LIPS,
        "FWPM_SUBLAYER_LIPS",
        "Legacy IPsec filters are added to this sublayer."
    },
    {
        // 15a66e17-3f3c-4f7b-aa6c-812aa613dd82
        FWPM_SUBLAYER_SECURE_SOCKET,
        "FWPM_SUBLAYER_SECURE_SOCKET",
        "Secure socket filters are added to this sublayer."
    },
    {
        // 337608b9-b7d5-4d5f-82f9-3618618bc058
        FWPM_SUBLAYER_TCP_CHIMNEY_OFFLOAD,
        "FWPM_SUBLAYER_TCP_CHIMNEY_OFFLOAD",
        "TCP Chimney Offload filters are added to this sublayer."
    },
    {
        // 877519e1-e6a9-41a5-81b4-8c4f118e4a60
        FWPM_SUBLAYER_INSPECTION,
        "FWPM_SUBLAYER_INSPECTION",
        "This is the lowest weighted sublayer. It is used only for inspection filters."
    },
    {
        // ba69dc66-5176-4979-9c89-26a7b46a8327
        FWPM_SUBLAYER_TEREDO,
        "FWPM_SUBLAYER_TEREDO",
        "Edge traversal filters are added to this sublayer."
    },
    {
        // ba69dc66-5176-4979-9c89-26a7b46a8327
        FWPM_SUBLAYER_EDGE_TRAVERSAL,
        "FWPM_SUBLAYER_EDGE_TRAVERSAL",
        "Edge traversal filters are added to this sublayer."
    },
    {
        // a5082e73-8f71-4559-8a9a-101cea04ef87
        FWPM_SUBLAYER_IPSEC_FORWARD_OUTBOUND_TUNNEL,
        "FWPM_SUBLAYER_IPSEC_FORWARD_OUTBOUND_TUNNEL",
        ""
    },
    {
        // e076d572-5d3d-48ef-802b-909eddb098bd
        FWPM_SUBLAYER_IPSEC_DOSP,
        "FWPM_SUBLAYER_IPSEC_DOSP",
        "IPsec forward outbound tunnel filters are added to this sublayer."
    },
    {
        // 24421dcf-0ac5-4caa-9e14-50f6e3636af0
        FWPM_SUBLAYER_TCP_TEMPLATES,
        "FWPM_SUBLAYER_TCP_TEMPLATES",
        "TCP template filters are added to this sublayer."
    },
    {
        // 37a57701-5884-4964-92b8-3e704688b0ad
        FWPM_SUBLAYER_IPSEC_SECURITY_REALM,
        "FWPM_SUBLAYER_IPSEC_SECURITY_REALM",
        "Unknown"
    },
};
#pragma endregion

///////////////////////////////////////////////////////////////////////////////
//
// GUIDs for built-in conditions
//
///////////////////////////////////////////////////////////////////////////////

#pragma region conditions

static fwpm_condition_desc_t fwpm_condition_desc_list[] = {
    {
        FWPM_CONDITION_INTERFACE_MAC_ADDRESS,
        "FWPM_CONDITION_INTERFACE_MAC_ADDRESS",
        ""
    },
    {
        FWPM_CONDITION_ALE_APP_ID,
        "FWPM_CONDITION_ALE_APP_ID",
        ""
    },
    {
        FWPM_CONDITION_MAC_LOCAL_ADDRESS,
       "FWPM_CONDITION_MAC_LOCAL_ADDRESS",
        ""
	},
    {
        FWPM_CONDITION_MAC_REMOTE_ADDRESS,
        "FWPM_CONDITION_MAC_REMOTE_ADDRESS",
        ""
	},
	{
	   FWPM_CONDITION_ETHER_TYPE,
	   "FWPM_CONDITION_ETHER_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_VLAN_ID,
	   "FWPM_CONDITION_VLAN_ID",
	   ""
	},
	{
	   FWPM_CONDITION_VSWITCH_TENANT_NETWORK_ID,
	   "FWPM_CONDITION_VSWITCH_TENANT_NETWORK_ID",
	   ""
	},
	{
	   FWPM_CONDITION_NDIS_PORT,
	   "FWPM_CONDITION_NDIS_PORT",
	   ""
	},
	{
	   FWPM_CONDITION_NDIS_MEDIA_TYPE,
	   "FWPM_CONDITION_NDIS_MEDIA_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_NDIS_PHYSICAL_MEDIA_TYPE,
	   "FWPM_CONDITION_NDIS_PHYSICAL_MEDIA_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_L2_FLAGS,
	   "FWPM_CONDITION_L2_FLAGS",
	   ""
	},
	{
	   FWPM_CONDITION_MAC_LOCAL_ADDRESS_TYPE,
	   "FWPM_CONDITION_MAC_LOCAL_ADDRESS_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_MAC_REMOTE_ADDRESS_TYPE,
	   "FWPM_CONDITION_MAC_REMOTE_ADDRESS_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_ALE_PACKAGE_ID,
	   "FWPM_CONDITION_ALE_PACKAGE_ID",
	   ""
	},
	{
	   FWPM_CONDITION_MAC_SOURCE_ADDRESS,
	   "FWPM_CONDITION_MAC_SOURCE_ADDRESS",
	   ""
	},
	{
	   FWPM_CONDITION_MAC_DESTINATION_ADDRESS,
	   "FWPM_CONDITION_MAC_DESTINATION_ADDRESS",
	   ""
	},
	{
	   FWPM_CONDITION_MAC_SOURCE_ADDRESS_TYPE,
	   "FWPM_CONDITION_MAC_SOURCE_ADDRESS_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_MAC_DESTINATION_ADDRESS_TYPE,
	   "FWPM_CONDITION_MAC_DESTINATION_ADDRESS_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_IP_SOURCE_PORT,
	   "FWPM_CONDITION_IP_SOURCE_PORT",
	   ""
	},
	{
	   FWPM_CONDITION_IP_DESTINATION_PORT,
	   "FWPM_CONDITION_IP_DESTINATION_PORT",
	   ""
	},
	{
	   FWPM_CONDITION_VSWITCH_ID,
	   "FWPM_CONDITION_VSWITCH_ID",
	   ""
	},
	{
	   FWPM_CONDITION_VSWITCH_NETWORK_TYPE,
	   "FWPM_CONDITION_VSWITCH_NETWORK_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_VSWITCH_SOURCE_INTERFACE_ID,
	   "FWPM_CONDITION_VSWITCH_SOURCE_INTERFACE_ID",
	   ""
	},
	{
	   FWPM_CONDITION_VSWITCH_DESTINATION_INTERFACE_ID,
	   "FWPM_CONDITION_VSWITCH_DESTINATION_INTERFACE_ID",
	   ""
	},
	{
	   FWPM_CONDITION_VSWITCH_SOURCE_VM_ID,
	   "FWPM_CONDITION_VSWITCH_SOURCE_VM_ID",
	   ""
	},
	{
	   FWPM_CONDITION_VSWITCH_DESTINATION_VM_ID,
	   "FWPM_CONDITION_VSWITCH_DESTINATION_VM_ID",
	   ""
	},
	{
	   FWPM_CONDITION_VSWITCH_SOURCE_INTERFACE_TYPE,
	   "FWPM_CONDITION_VSWITCH_SOURCE_INTERFACE_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_VSWITCH_DESTINATION_INTERFACE_TYPE,
	   "FWPM_CONDITION_VSWITCH_DESTINATION_INTERFACE_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_ALE_SECURITY_ATTRIBUTE_FQBN_VALUE,
	   "FWPM_CONDITION_ALE_SECURITY_ATTRIBUTE_FQBN_VALUE",
	   ""
	},
	{
	   FWPM_CONDITION_IPSEC_SECURITY_REALM_ID,
	   "FWPM_CONDITION_IPSEC_SECURITY_REALM_ID",
	   ""
	},
	{
		FWPM_CONDITION_ALE_EFFECTIVE_NAME,
		"FWPM_CONDITION_ALE_EFFECTIVE_NAME",
	   ""
	},
	{
	   FWPM_CONDITION_IP_LOCAL_ADDRESS,
	   "FWPM_CONDITION_IP_LOCAL_ADDRESS",
	   ""
	},
	{
	   FWPM_CONDITION_IP_REMOTE_ADDRESS,
	   "FWPM_CONDITION_IP_REMOTE_ADDRESS",
	   ""
	},
	{
	   FWPM_CONDITION_IP_SOURCE_ADDRESS,
	   "FWPM_CONDITION_IP_SOURCE_ADDRESS",
	   ""
	},
	{
	   FWPM_CONDITION_IP_DESTINATION_ADDRESS,
	   "FWPM_CONDITION_IP_DESTINATION_ADDRESS",
	   ""
	},
	{
	   FWPM_CONDITION_IP_LOCAL_ADDRESS_TYPE,
	   "FWPM_CONDITION_IP_LOCAL_ADDRESS_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_IP_DESTINATION_ADDRESS_TYPE,
	   "FWPM_CONDITION_IP_DESTINATION_ADDRESS_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_BITMAP_IP_LOCAL_ADDRESS,
	   "FWPM_CONDITION_BITMAP_IP_LOCAL_ADDRESS",
	   ""
	},
	{
	  FWPM_CONDITION_BITMAP_IP_LOCAL_PORT,
	  "FWPM_CONDITION_BITMAP_IP_LOCAL_PORT",
	   ""
	},
	{
	 FWPM_CONDITION_BITMAP_IP_REMOTE_ADDRESS,
	 "FWPM_CONDITION_BITMAP_IP_REMOTE_ADDRESS",
	   ""
	},
	{
	  FWPM_CONDITION_BITMAP_IP_REMOTE_PORT,
	  "FWPM_CONDITION_BITMAP_IP_REMOTE_PORT",
	   ""
	},
	{
	   FWPM_CONDITION_IP_NEXTHOP_ADDRESS,
	   "FWPM_CONDITION_IP_NEXTHOP_ADDRESS",
	   ""
	},
	{
	  FWPM_CONDITION_BITMAP_INDEX_KEY,
	  "FWPM_CONDITION_BITMAP_INDEX_KEY",
	   ""
	},
	{
	   FWPM_CONDITION_IP_LOCAL_INTERFACE,
	   "FWPM_CONDITION_IP_LOCAL_INTERFACE",
	   ""
	},
	{
	   FWPM_CONDITION_IP_ARRIVAL_INTERFACE,
	   "FWPM_CONDITION_IP_ARRIVAL_INTERFACE",
	   ""
	},
	{
	   FWPM_CONDITION_ARRIVAL_INTERFACE_TYPE,
	   "FWPM_CONDITION_ARRIVAL_INTERFACE_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_ARRIVAL_TUNNEL_TYPE,
	   "FWPM_CONDITION_ARRIVAL_TUNNEL_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_ARRIVAL_INTERFACE_INDEX,
	   "FWPM_CONDITION_ARRIVAL_INTERFACE_INDEX",
	   ""
	},
	{
	   FWPM_CONDITION_NEXTHOP_SUB_INTERFACE_INDEX,
	   "FWPM_CONDITION_NEXTHOP_SUB_INTERFACE_INDEX",
	   ""
	},
	{
	   FWPM_CONDITION_IP_NEXTHOP_INTERFACE,
	   "FWPM_CONDITION_IP_NEXTHOP_INTERFACE",
	   ""
	},
	{
	   FWPM_CONDITION_NEXTHOP_INTERFACE_TYPE,
	   "FWPM_CONDITION_NEXTHOP_INTERFACE_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_NEXTHOP_TUNNEL_TYPE,
	   "FWPM_CONDITION_NEXTHOP_TUNNEL_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_NEXTHOP_INTERFACE_INDEX,
	   "FWPM_CONDITION_NEXTHOP_INTERFACE_INDEX",
	   ""
	},
	{
	   FWPM_CONDITION_ORIGINAL_PROFILE_ID,
	   "FWPM_CONDITION_ORIGINAL_PROFILE_ID",
	   ""
	},
	{
	   FWPM_CONDITION_CURRENT_PROFILE_ID,
	   "FWPM_CONDITION_CURRENT_PROFILE_ID",
	   ""
	},
	{
	   FWPM_CONDITION_LOCAL_INTERFACE_PROFILE_ID,
	   "FWPM_CONDITION_LOCAL_INTERFACE_PROFILE_ID",
	   ""
	},
	{
	   FWPM_CONDITION_ARRIVAL_INTERFACE_PROFILE_ID,
	   "FWPM_CONDITION_ARRIVAL_INTERFACE_PROFILE_ID",
	   ""
	},
	{
	   FWPM_CONDITION_NEXTHOP_INTERFACE_PROFILE_ID,
	   "FWPM_CONDITION_NEXTHOP_INTERFACE_PROFILE_ID",
	   ""
	},
	{
	   FWPM_CONDITION_REAUTHORIZE_REASON,
	   "FWPM_CONDITION_REAUTHORIZE_REASON",
	   ""
	},
	{
	   FWPM_CONDITION_ORIGINAL_ICMP_TYPE,
	   "FWPM_CONDITION_ORIGINAL_ICMP_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_IP_PHYSICAL_ARRIVAL_INTERFACE,
	   "FWPM_CONDITION_IP_PHYSICAL_ARRIVAL_INTERFACE",
	   ""
	},
	{
	   FWPM_CONDITION_IP_PHYSICAL_NEXTHOP_INTERFACE,
	   "FWPM_CONDITION_IP_PHYSICAL_NEXTHOP_INTERFACE",
	   ""
	},
	{
	   FWPM_CONDITION_INTERFACE_QUARANTINE_EPOCH,
	   "FWPM_CONDITION_INTERFACE_QUARANTINE_EPOCH",
	   ""
	},
	{
	   FWPM_CONDITION_INTERFACE_TYPE,
	   "FWPM_CONDITION_INTERFACE_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_TUNNEL_TYPE,
	   "FWPM_CONDITION_TUNNEL_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_IP_FORWARD_INTERFACE,
	   "FWPM_CONDITION_IP_FORWARD_INTERFACE",
	   ""
	},
	{
	   FWPM_CONDITION_IP_PROTOCOL,
	   "FWPM_CONDITION_IP_PROTOCOL",
	   ""
	},
	{
	   FWPM_CONDITION_IP_LOCAL_PORT,
	   "FWPM_CONDITION_IP_LOCAL_PORT",
	   ""
	},
	{
	   FWPM_CONDITION_IP_REMOTE_PORT,
	   "FWPM_CONDITION_IP_REMOTE_PORT",
	   ""
	},
	{
	   FWPM_CONDITION_EMBEDDED_LOCAL_ADDRESS_TYPE,
	   "FWPM_CONDITION_EMBEDDED_LOCAL_ADDRESS_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_EMBEDDED_REMOTE_ADDRESS,
	   "FWPM_CONDITION_EMBEDDED_REMOTE_ADDRESS",
	   ""
	},
	{
	   FWPM_CONDITION_EMBEDDED_PROTOCOL,
	   "FWPM_CONDITION_EMBEDDED_PROTOCOL",
	   ""
	},
	{
	   FWPM_CONDITION_EMBEDDED_LOCAL_PORT,
	   "FWPM_CONDITION_EMBEDDED_LOCAL_PORT",
	   ""
	},
	{
	   FWPM_CONDITION_EMBEDDED_REMOTE_PORT,
	   "FWPM_CONDITION_EMBEDDED_REMOTE_PORT",
	   ""
	},
	{
	   FWPM_CONDITION_FLAGS,
	   "FWPM_CONDITION_FLAGS",
	   ""
	},
	{
	   FWPM_CONDITION_DIRECTION,
	   "FWPM_CONDITION_DIRECTION",
	   ""
	},
	{
	   FWPM_CONDITION_INTERFACE_INDEX,
	   "FWPM_CONDITION_INTERFACE_INDEX",
	   ""
	},
	{
	   FWPM_CONDITION_SUB_INTERFACE_INDEX,
	   "FWPM_CONDITION_SUB_INTERFACE_INDEX",
	   ""
	},
	{
	   FWPM_CONDITION_SOURCE_INTERFACE_INDEX,
	   "FWPM_CONDITION_SOURCE_INTERFACE_INDEX",
	   ""
	},
	{
	   FWPM_CONDITION_SOURCE_SUB_INTERFACE_INDEX,
	   "FWPM_CONDITION_SOURCE_SUB_INTERFACE_INDEX",
	   ""
	},
	{
	   FWPM_CONDITION_DESTINATION_INTERFACE_INDEX,
	   "FWPM_CONDITION_DESTINATION_INTERFACE_INDEX",
	   ""
	},
	{
	   FWPM_CONDITION_DESTINATION_SUB_INTERFACE_INDEX,
	   "FWPM_CONDITION_DESTINATION_SUB_INTERFACE_INDEX",
	   ""
	},
	{
	   FWPM_CONDITION_ALE_ORIGINAL_APP_ID,
	   "FWPM_CONDITION_ALE_ORIGINAL_APP_ID",
	   ""
	},
	{
	   FWPM_CONDITION_ALE_USER_ID,
	   "FWPM_CONDITION_ALE_USER_ID",
	   ""
	},
	{
	   FWPM_CONDITION_ALE_REMOTE_USER_ID,
	   "FWPM_CONDITION_ALE_REMOTE_USER_ID",
	   ""
	},
	{
	   FWPM_CONDITION_ALE_REMOTE_MACHINE_ID,
	   "FWPM_CONDITION_ALE_REMOTE_MACHINE_ID",
	   ""
	},
	{
	   FWPM_CONDITION_ALE_PROMISCUOUS_MODE,
	   "FWPM_CONDITION_ALE_PROMISCUOUS_MODE",
	   ""
	},
	{
	   FWPM_CONDITION_ALE_SIO_FIREWALL_SYSTEM_PORT,
	   "FWPM_CONDITION_ALE_SIO_FIREWALL_SYSTEM_PORT",
	   ""
	},
	{
	   FWPM_CONDITION_ALE_REAUTH_REASON,
	   "FWPM_CONDITION_ALE_REAUTH_REASON",
	   ""
	},
	{
	   FWPM_CONDITION_ALE_NAP_CONTEXT,
	   "FWPM_CONDITION_ALE_NAP_CONTEXT",
	   ""
	},
	{
	   FWPM_CONDITION_KM_AUTH_NAP_CONTEXT,
	   "FWPM_CONDITION_KM_AUTH_NAP_CONTEXT",
	   ""
	},
	{
		FWPM_CONDITION_REMOTE_USER_TOKEN,
		"FWPM_CONDITION_REMOTE_USER_TOKEN",
	   ""
	},
	{
	   FWPM_CONDITION_RPC_IF_UUID,
	   "FWPM_CONDITION_RPC_IF_UUID",
	   ""
	},
	{
	   FWPM_CONDITION_RPC_IF_VERSION,
	   "FWPM_CONDITION_RPC_IF_VERSION",
	   ""
	},
	{
		FWPM_CONDITION_RPC_IF_FLAG,
		"FWPM_CONDITION_RPC_IF_FLAG",
	   ""
	},
	{
		FWPM_CONDITION_DCOM_APP_ID,
		"FWPM_CONDITION_DCOM_APP_ID",
	   ""
	},
	{
		FWPM_CONDITION_IMAGE_NAME,
		"FWPM_CONDITION_IMAGE_NAME",
	   ""
	},
	{
		FWPM_CONDITION_RPC_PROTOCOL,
		"FWPM_CONDITION_RPC_PROTOCOL",
	   ""
	},
	{
	   FWPM_CONDITION_RPC_AUTH_TYPE,
	   "FWPM_CONDITION_RPC_AUTH_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_RPC_AUTH_LEVEL,
	   "FWPM_CONDITION_RPC_AUTH_LEVEL",
	   ""
	},
	{
	   FWPM_CONDITION_SEC_ENCRYPT_ALGORITHM,
	   "FWPM_CONDITION_SEC_ENCRYPT_ALGORITHM",
	   ""
	},
	{
		FWPM_CONDITION_SEC_KEY_SIZE,
		"FWPM_CONDITION_SEC_KEY_SIZE",
	   ""
	},
	{
	   FWPM_CONDITION_IP_LOCAL_ADDRESS_V4,
	   "FWPM_CONDITION_IP_LOCAL_ADDRESS_V4",
	   ""
	},
	{
	   FWPM_CONDITION_IP_LOCAL_ADDRESS_V6,
	   "FWPM_CONDITION_IP_LOCAL_ADDRESS_V6",
	   ""
	},
	{
		FWPM_CONDITION_PIPE,
		"FWPM_CONDITION_PIPE",
	   ""
	},
	{
	   FWPM_CONDITION_IP_REMOTE_ADDRESS_V4,
	   "FWPM_CONDITION_IP_REMOTE_ADDRESS_V4",
	   ""
	},
	{
	   FWPM_CONDITION_IP_REMOTE_ADDRESS_V6,
	   "FWPM_CONDITION_IP_REMOTE_ADDRESS_V6",
	   ""
	},
	{
		FWPM_CONDITION_PROCESS_WITH_RPC_IF_UUID,
		"FWPM_CONDITION_PROCESS_WITH_RPC_IF_UUID",
	   ""
	},
	{
		FWPM_CONDITION_RPC_EP_VALUE,
		"FWPM_CONDITION_RPC_EP_VALUE",
	   ""
	},
	{
		FWPM_CONDITION_RPC_EP_FLAGS,
		"FWPM_CONDITION_RPC_EP_FLAGS",
	   ""
	},
	{
		FWPM_CONDITION_CLIENT_TOKEN,
		"FWPM_CONDITION_CLIENT_TOKEN",
	   ""
	},
	{
		FWPM_CONDITION_RPC_SERVER_NAME,
		"FWPM_CONDITION_RPC_SERVER_NAME",
	   ""
	},
	{
		FWPM_CONDITION_RPC_SERVER_PORT,
		"FWPM_CONDITION_RPC_SERVER_PORT",
	   ""
	},
	{
		FWPM_CONDITION_RPC_PROXY_AUTH_TYPE,
		"FWPM_CONDITION_RPC_PROXY_AUTH_TYPE",
	   ""
	},
	{
		FWPM_CONDITION_CLIENT_CERT_KEY_LENGTH,
		"FWPM_CONDITION_CLIENT_CERT_KEY_LENGTH",
	   ""
	},
	{
		FWPM_CONDITION_CLIENT_CERT_OID,
		"FWPM_CONDITION_CLIENT_CERT_OID",
	   ""
	},
	{
	   FWPM_CONDITION_NET_EVENT_TYPE,
	   "FWPM_CONDITION_NET_EVENT_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_PEER_NAME,
	   "FWPM_CONDITION_PEER_NAME",
	   ""
	},
	{
	   FWPM_CONDITION_REMOTE_ID,
	   "FWPM_CONDITION_REMOTE_ID",
	   ""
	},
	{
	   FWPM_CONDITION_AUTHENTICATION_TYPE,
	   "FWPM_CONDITION_AUTHENTICATION_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_KM_TYPE,
	   "FWPM_CONDITION_KM_TYPE",
	   ""
	},
	{
	   FWPM_CONDITION_KM_MODE,
	   "FWPM_CONDITION_KM_MODE",
	   ""
	},
	{
	   FWPM_CONDITION_IPSEC_POLICY_KEY,
	   "FWPM_CONDITION_IPSEC_POLICY_KEY",
	   ""
	},
	{
	   FWPM_CONDITION_QM_MODE,
	   "FWPM_CONDITION_QM_MODE",
	   ""
	},
	{
		FWPM_CONDITION_COMPARTMENT_ID,
		"FWPM_CONDITION_COMPARTMENT_ID",
	   ""
	},
	{
	   FWPM_CONDITION_RESERVED0,
	   "FWPM_CONDITION_RESERVED0",
	   ""
	},
	{
	   FWPM_CONDITION_RESERVED1,
	   "FWPM_CONDITION_RESERVED1",
	   ""
	},
	{
	   FWPM_CONDITION_RESERVED2,
	   "FWPM_CONDITION_RESERVED2",
	   ""
	},
	{
	   FWPM_CONDITION_RESERVED3,
	   "FWPM_CONDITION_RESERVED3",
	   ""
	},
	{
	   FWPM_CONDITION_RESERVED4,
	   "FWPM_CONDITION_RESERVED4",
	   ""
	},
	{
	   FWPM_CONDITION_RESERVED5,
	   "FWPM_CONDITION_RESERVED5",
	   ""
	},
	{
		FWPM_CONDITION_RESERVED6,
		"FWPM_CONDITION_RESERVED6",
	   ""
	},
	{
		FWPM_CONDITION_RESERVED7,
		"FWPM_CONDITION_RESERVED7",
	   ""
	},
	{
		FWPM_CONDITION_RESERVED8,
		"FWPM_CONDITION_RESERVED8",
	   ""
	},
	{
		FWPM_CONDITION_RESERVED9,
		"FWPM_CONDITION_RESERVED9",
	   ""
	},
	{
		FWPM_CONDITION_RESERVED10,
		"FWPM_CONDITION_RESERVED10",
	   ""
	},
	{
		FWPM_CONDITION_RESERVED11,
		"FWPM_CONDITION_RESERVED11",
	   ""
	},
	{
		FWPM_CONDITION_RESERVED12,
		"FWPM_CONDITION_RESERVED12",
	   ""
	},
	{
		FWPM_CONDITION_RESERVED13,
		"FWPM_CONDITION_RESERVED13",
	   ""
	},
	{
		FWPM_CONDITION_RESERVED14,
		"FWPM_CONDITION_RESERVED14",
	   ""
	},
	{
		FWPM_CONDITION_RESERVED15,
		"FWPM_CONDITION_RESERVED15",
	   ""
	},
};
#pragma endregion 

#pragma region funcs
/// <summary>
/// Look up layer information on layer GUID 
/// </summary>
/// <param name="fwpm_layer_guid">layer GUID</param>
/// <param name="fwpm_layer_desc">layer information struct</param>
/// <returns></returns>
bool print_fwpm_layer_desc_guidance(GUID fwpm_layer_guid, fwpm_layer_desc_t* fwpm_layer_desc)
{
    size_t idx = 0;
    size_t ttl = sizeof fwpm_layer_desc_list / sizeof fwpm_layer_desc_list[0];

	fwpm_layer_desc_t default_fwpm_layer = { GUID_NULL, "",  "" };

    for (idx = 0; idx < ttl; idx++) {
        // if (fwpm_layer_guid == fwpm_layer_desc_list[idx].guid) {
        if (IsEqualGUID(fwpm_layer_guid,fwpm_layer_desc_list[idx].guid)) {
			fwpm_layer_desc->guid = fwpm_layer_desc_list[idx].guid;
			fwpm_layer_desc->msg = fwpm_layer_desc_list[idx].msg;
			fwpm_layer_desc->desc = fwpm_layer_desc_list[idx].desc;
			break;
        }
    }

	if (idx == ttl) {
		fwpm_layer_desc = &default_fwpm_layer;
		return false;
	}
	return true;
}

bool print_fwpm_layer_desc_guidance(std::string fwpm_layer_msg, fwpm_layer_desc_t* fwpm_layer_desc)
{
	size_t idx = 0;
	size_t ttl = sizeof fwpm_layer_desc_list / sizeof fwpm_layer_desc_list[0];

	fwpm_layer_desc_t default_fwpm_layer = { GUID_NULL, "",  "" };

	for (idx = 0; idx < ttl; idx++) {
		if (fwpm_layer_msg.compare(fwpm_layer_desc_list[idx].msg)  == 0) {
			fwpm_layer_desc->guid = fwpm_layer_desc_list[idx].guid;
			fwpm_layer_desc->msg = fwpm_layer_desc_list[idx].msg;
			fwpm_layer_desc->desc = fwpm_layer_desc_list[idx].desc;
			break;
		}
	}

	if (idx == ttl) {
		fwpm_layer_desc = &default_fwpm_layer;
		return false;
	}
	return true;
}

bool getSublayerGuidance(GUID fwpm_sublayer_guid, std::unique_ptr<fwpm_sublayer_desc_t>& fwpm_sublayer_desc)
{
	size_t idx = 0;
	size_t ttl = sizeof fwpm_sublayer_desc_list / sizeof fwpm_sublayer_desc_list[0];

	fwpm_sublayer_desc_t default_fwpm_sublayer = { GUID_NULL, "",  "" };

	for (idx = 0; idx < ttl; idx++) {
		if (IsEqualGUID(fwpm_sublayer_guid, fwpm_sublayer_desc_list[idx].guid)) {
			fwpm_sublayer_desc->guid = fwpm_sublayer_desc_list[idx].guid;
			fwpm_sublayer_desc->msg = fwpm_sublayer_desc_list[idx].msg;
			fwpm_sublayer_desc->desc = fwpm_sublayer_desc_list[idx].desc;
			break;
		}
	}

	if (idx == ttl) {
		// fwpm_sublayer_desc = &default_fwpm_sublayer;
		fwpm_sublayer_desc->guid = default_fwpm_sublayer.guid;
		fwpm_sublayer_desc->msg = default_fwpm_sublayer.msg;
		fwpm_sublayer_desc->desc = default_fwpm_sublayer.desc;
		return false;
	}
	return true;
}

bool getLayerGuidance(GUID fwpm_layer_guid, std::unique_ptr<fwpm_layer_desc_t>& fwpm_layer_desc)
{
	size_t idx = 0;
	size_t ttl = sizeof fwpm_layer_desc_list / sizeof fwpm_layer_desc_list[0];

	fwpm_layer_desc_t default_fwpm_layer = { GUID_NULL, "",  "" };

	for (idx = 0; idx < ttl; idx++) {
		if (IsEqualGUID(fwpm_layer_guid, fwpm_layer_desc_list[idx].guid)) {
			fwpm_layer_desc->guid = fwpm_layer_desc_list[idx].guid;
			fwpm_layer_desc->msg = fwpm_layer_desc_list[idx].msg;
			fwpm_layer_desc->desc = fwpm_layer_desc_list[idx].desc;
			break;
		}
	}

	if (idx == ttl) {
		fwpm_layer_desc->guid = default_fwpm_layer.guid;
		fwpm_layer_desc->msg = default_fwpm_layer.msg;
		fwpm_layer_desc->desc = default_fwpm_layer.desc;
		return false;
	}
	return true;
}

bool getLayerGuidance(std::string fwpm_layer_msg, std::unique_ptr<fwpm_layer_desc_t>& fwpm_layer_desc)
{
	size_t idx = 0;
	size_t ttl = sizeof fwpm_layer_desc_list / sizeof fwpm_layer_desc_list[0];

	fwpm_layer_desc_t default_fwpm_layer = { GUID_NULL, "",  "" };

	for (idx = 0; idx < ttl; idx++) {
		if (fwpm_layer_msg.compare(fwpm_layer_desc_list[idx].msg) == 0) {
			fwpm_layer_desc->guid = fwpm_layer_desc_list[idx].guid;
			fwpm_layer_desc->msg = fwpm_layer_desc_list[idx].msg;
			fwpm_layer_desc->desc = fwpm_layer_desc_list[idx].desc;
			break;
		}
	}

	if (idx == ttl) {
		fwpm_layer_desc->guid = default_fwpm_layer.guid;
		fwpm_layer_desc->msg = default_fwpm_layer.msg;
		fwpm_layer_desc->desc = default_fwpm_layer.desc;
		return false;
	}
	return true;
}

bool print_fwpm_condition_desc_guidance(GUID fwpm_condition_guid, fwpm_condition_desc_t* fwpm_condition_desc)
{
	size_t idx = 0;
	size_t ttl = sizeof fwpm_condition_desc_list / sizeof fwpm_condition_desc_list[0];

	fwpm_condition_desc_t default_fwpm_condition = { GUID_NULL, "",  "" };

	for (idx = 0; idx < ttl; idx++) {
		if (IsEqualGUID(fwpm_condition_guid, fwpm_condition_desc_list[idx].guid)) {
			fwpm_condition_desc->guid = fwpm_condition_desc_list[idx].guid;
			fwpm_condition_desc->msg = fwpm_condition_desc_list[idx].msg;
			fwpm_condition_desc->desc = fwpm_condition_desc_list[idx].desc;
			break;
		}
	}

	if (idx == ttl) {
		fwpm_condition_desc = &default_fwpm_condition;
		return false;
	}
	return true;
}

#pragma endregion
