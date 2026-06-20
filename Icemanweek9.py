#!/usr/bin/env python3

import os
from pcapfile import savefile
from prettytable import PrettyTable
import socket

# Optional: Known port descriptions
PORT_DESCRIPTIONS = {
    102: "MSExchangeMTA X.400 / ISO-TSAP Class 0",
    123: "Network Time Protocol",
    1379: "Integrity Solutions",
    1400: "Cadkey Tablet Daemon",
    1433: "IBM CICS",
    11110: "Client status info",
    11111: "Viral Computing Environment (VCE)",
    1208: "SEAGULL AIS",
    1611: "NetBill Credential Server",
    1680: "microcom-sbp",
    1780: "dpkeyserv",
    54320: "Orifice 2000 (TCP)",
    54283: "SubSeven",
    52673: "Stickies",
    51515: "Microsoft Operations Manager MOM-Clear",
}

def get_port_description(port):
    return PORT_DESCRIPTIONS.get(port, "")

def parse_pcap(file_path):
    with open(file_path, 'rb') as f:
        capfile = savefile.load_savefile(f, layers=4, verbose=False)

    connections = {}
    ports = {}

    for pkt in capfile.packets:
        eth_frame = pkt.packet

        # Ensure nested payloads exist
        if not hasattr(eth_frame, 'payload') or not hasattr(eth_frame.payload, 'payload'):
            continue

        ip_packet = eth_frame.payload
        transport = ip_packet.payload

        src_ip = ip_packet.src
        dst_ip = ip_packet.dst
        src_port = getattr(transport, 'src_port', None)
        dst_port = getattr(transport, 'dst_port', None)
        protocol = getattr(ip_packet, 'protocol', None)

        # Skip if any essential field is missing
        if protocol is None or src_port is None or dst_port is None:
            continue

        conn_key = (src_ip, src_port, dst_ip, dst_port, protocol)
        if conn_key not in connections:
            connections[conn_key] = {"packet_count": 0, "total_bytes": 0}

        connections[conn_key]["packet_count"] += 1
        connections[conn_key]["total_bytes"] += len(pkt.raw())

        for ip, port in [(src_ip, src_port), (dst_ip, dst_port)]:
            if (ip, port) not in ports:
                ports[(ip, port)] = 0
            ports[(ip, port)] += 1

    return connections, ports

def generate_report(pcap_filename, connections, ports, output_dir="reports"):
    os.makedirs(output_dir, exist_ok=True)
    base_name = os.path.splitext(os.path.basename(pcap_filename))[0]
    report_path = os.path.join(output_dir, f"{base_name}_report.txt")

    with open(report_path, 'w') as f:
        f.write(f"Report for: {pcap_filename}\n\n")

        conn_table = PrettyTable()
        conn_table.field_names = ["Source IP", "Src Port", "Destination IP", "Dst Port", "Protocol", "Packets", "Bytes"]

        for (src_ip, src_port, dst_ip, dst_port, proto), stats in connections.items():
            conn_table.add_row([src_ip, src_port, dst_ip, dst_port, proto, stats['packet_count'], stats['total_bytes']])

        f.write("=== Unique Connections ===\n")
        f.write(conn_table.get_string() + "\n\n")

        port_table = PrettyTable()
        port_table.field_names = ["IP", "PORT", "PORT-DESCRIPTION"]

        for (ip, port), _ in ports.items():
            desc = get_port_description(port)
            port_table.add_row([ip, port, desc])

        f.write("=== PORT Observations ===\n")
        f.write(port_table.get_string() + "\n")

    print(f"[✓] Report saved: {report_path}")

if __name__ == "__main__":
    import sys
    import glob

    if len(sys.argv) > 1:
        # Drag-and-drop support
        for pcap in sys.argv[1:]:
            print(f"[+] Processing {pcap}...")
            conns, ports = parse_pcap(pcap)
            generate_report(pcap, conns, ports)
    else:
        # Default: scan pcap_files/ directory
        pcap_dir = "pcap_files"
        pcap_files = glob.glob(os.path.join(pcap_dir, "*.pcap"))

        for pcap in pcap_files:
            print(f"[+] Processing {pcap}...")
            conns, ports = parse_pcap(pcap)
            generate_report(pcap, conns, ports)
