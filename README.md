
libipfix (forked version of 1.0 with many patches to make json-milestone-2 or so)

This package contains source code for a library to export and 
collect IPFIX measurement and accounting data. 
The library is complemented with an IPFIX collector and
a basic IPFIX probe.

The library supports IPFIX (draft-ietf-ipfix-protocol-24.txt,
draft-ietf-ipfix-info-15.txt, draft-ietf-psamp-info-05.txt)
and Netflow9 (RFC 3954) using TCP, UDP and SCTP as transport protocol.

There are some small example programs containing code that 
demonstrates how to use the library.

Find more information at
http://libipfix.sourceforge.net/ (upstream; will not relate to this fork)

The latest release is available from
http://sourceforge.net/projects/libipfix/  (upstream)
https://github.com/cameronkerrnz/libipfix  (this fork)

Please send inquiries/comments/reports about this fork to Cameron Kerr <cameron.kerr.nz@gmail.com>

Compiling (for JSONlines output)
===

As for Red Hat Enterprise Linux 6. I hope to make an RPM for the next release.

~~~
sudo yum install "@Development Tools" libpcap-devel
git clone https://cameronkerrnz@github.com/cameronkerrnz/libipfix.git
cd libipfix
./configure --prefix=/opt/libipfix --enable-jsonlines --enable-fallback-templates
make
make   # yes, a second time to work around some faulty Makefile rules (patch welcome!)
sudo make install
~~~

Running the software initially
===

Because the transcript above had the libraries installed in a non-standard place, we can set LD_LIBRARY_PATH, or add the path to /etc/ld.so.conf.d/libipfix, or ... I'm sure there's a more clever way of specifying this with the linker...

~~~
$ LD_LIBRARY_PATH=/opt/libipfix/lib /opt/libipfix/bin/ipfix_collector --help

ipfix collector ($Revision: 1.12 $ Mar 26 2015)

usage: ipfix_collector [options]

options:
  -h                          this help
  -4                          accept connections via AF_INET socket
  -6                          accept connections via AF_INET6 socket
  -o <datadir>                store files of collected data in this dir
  -p <portno>                 listen on this port (default=4739)
  -s                          support SCTP clients
  -t                          support TCP clients
  -u                          support UDP clients
  -v                          increase verbose level
jsonlines options:
  --json                      export JSON to a file; one JSON doc/line
  --jsonfile <filename>       file to append to, or '-' for stdout
  --json-record-unknown-sets         include bytes of sets dropped due to no template
fallback templates:
  --fallback-templates=netscaler

example: ipfix_collector -stu -vv -o .
~~~

Let's test that we can receive our IPFIX / Appflow messages. Ensure you have configured your appliance to send to the port that you will listen to (the standard ipfix port is UDP/4739 -- ipfix is also specified on TCP and SCTP -- I have only tested / developed with UDP currently, because that is all that the Netscalers offer).

It is useful to bear in mind that this traffic is both unencrypted and unauthenticated, other by whatever network layer resrictions you provide.

We'll write the output to a file /tmp/data.json

~~~
$ LD_LIBRARY_PATH=/opt/libipfix/lib /opt/libipfix/bin/ipfix_collector -4 -u -vv --json --jsonfile /tmp/data.json --fallback-templates=netscaler
[ipfix_collector] listen on port 4739, write to stdout ...
[ipfix_collector] data goes to file /tmp/data.json as one JSON document per line
... you should soon see DATA RECORDS and TEMPLATE RECORDS flow up your screen with -vv
...
Template source is fallback for template ID 258
DATA RECORD:
 template id:  258
 nfields:      37
 observationPointId: 6914017
 exportingProcessId: 0
 flowId: 27059599
 netscaler_transaction_id: 2958993
 netscaler_connection_id: 27059599
 ipVersion: 4
 protocolIdentifier: 6
 paddingOctets: 0x0000
 sourceIPv4Address: «IP»
 destinationIPv4Address: «IP»
 sourceTransportPort: 50473
 destinationTransportPort: 443
 packetDeltaCount: 1
 octetDeltaCount: 682
 tcpControlBits: 24
 netscaler_flow_flags: 84025344
 flowStartMicroseconds: 15617890647616118639
 flowEndMicroseconds: 15617890647616118639
 ingressInterface: 2
 egressInterface: 2147483651
 netscaler_app_name_app_id: 9541
 netscaler_app_unit_name_app_id: 0
 netscaler_http_res_forw_fb: 0
 netscaler_http_res_forw_lb: 0
 netscaler_connection_chain_id: 0x00000000000000000000000000000000
 netscaler_connection_chain_hop_count: 0
 netscaler_http_req_url: «Request URL»
 netscaler_http_req_cookie: «Cookies sent»
 netscaler_http_req_referer: «HTTP referrer»
 netscaler_http_req_method: GET
 netscaler_http_req_host: «HTTP host header»
 netscaler_http_req_user_agent: «HTTP user-agent string»
 netscaler_http_content_type:
 netscaler_http_req_authorization:
 netscaler_http_req_via:
 netscaler_http_req_x_forwarded_for:
 netscaler_http_domain_name:
...
^C
[ipfix_collector] got signo 2, bye.
~~~

I've anonymised various fields.

Now have a look at /tmp/data.json. Because its all one long line, I'll reformat it to show one line on multiple lines, using Python's pretty-printer.

~~~
$ tail -1 /tmp/data.json | python -mjson.tool
{
    "destinationIPv4Address": "«IP»",
    "destinationTransportPort": 443,
    "egressInterface": 2147483651,
    "exportingProcessId": 0,
    "flowEndMicroseconds": "2015-03-26T01:52:12.000Z",
    "flowId": 27059599,
    "flowStartMicroseconds": "2015-03-26T01:52:12.000Z",
    "ingressInterface": 2,
    "ipVersion": 4,
    "ipfix_exporter_ip": "«IP»",
    "ipfix_template_id": "258",
    "ipfix_template_source": "fallback",
    "ipfix_timestamp": "2015-03-26T01:52:12Z",
    "netscaler_app_name_app_id": 9541,
    "netscaler_app_unit_name_app_id": 0,
    "netscaler_connection_chain_hop_count": 0,
    "netscaler_connection_chain_id": "00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00",
    "netscaler_connection_id": 27059599,
    "netscaler_flow_flags": 84025344,
    "netscaler_http_req_cookie": "«Cookies»",
    "netscaler_http_req_host": "«Host»",
    "netscaler_http_req_method": "GET",
    "netscaler_http_req_referer": "«Referrer»",
    "netscaler_http_req_url": "«Request URI»",
    "netscaler_http_req_user_agent": "«User agent»",
    "netscaler_http_res_forw_fb": "2036-02-07T06:28:16.000Z",
    "netscaler_http_res_forw_lb": "2036-02-07T06:28:16.000Z",
    "netscaler_transaction_id": 2958993,
    "observationPointId": 6914017,
    "octetDeltaCount": 682,
    "packetDeltaCount": 1,
    "protocolIdentifier": 6,
    "sourceIPv4Address": "«IP»",
    "sourceTransportPort": 50473,
    "tcpControlBits": 24
}
~~~

At this point, its useful to remember that every LINE is a separate JSON document. But the FILE is *NOT* a valid JSON data-structure, so you can't process the file (or more than one line of the file) using a tool that expects JSON (unless it can handle JSONlines).

~~~
$ tail -2 /tmp/data.json | python -mjson.tool
Extra data: line 2 column 1 - line 3 column 1 (char 911 - 2430)
~~~
 
