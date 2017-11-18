DISCONTUING WORK ON THIS PROJECT
===

I'm going to look at using https://github.com/logstash-plugins/logstash-codec-netflow instead, which is at least more actively
maintained than I can resource for this particular project.





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
git clone https://github.com/cameronkerrnz/libipfix.git
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

I've anonymised various fields.  Now have a look at /tmp/data.json. Because its
all one long line, I'll reformat it to show one line on multiple lines, using
Python's pretty-printer.

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

At this point, its useful to remember that every LINE is a separate JSON
document. But the FILE is **NOT** a valid JSON data-structure, so you can't
process the file (or more than one line of the file) using a tool that expects
JSON (unless it can handle JSONlines).

Note: did you know that proper JSON says to escape the '/' character? That may
come as something of a surprise to you. You'll also perhaps notice that the
NetScaler logs already excape the URL according to the Common Logging Format
(CLF) convention. I shall perhaps look at decoding them and encoding them as
UTF-8, but that is not a priority.

~~~
$ tail -2 /tmp/data.json | python -mjson.tool
Extra data: line 2 column 1 - line 3 column 1 (char 911 - 2430)
~~~

Running as a daemon
===

Run this under a system such as SystemD or Supervisord. I'm deploying this on RHEL6 with Supervisord installed from pip (and currently requires Python 2.7, which you can get from Red Hat's SCL channel.

There is an example supervisord configuration in the doc/ directory.


Add a service account
===

I'll create a local user that this software will run as. That user will only
need access to write to the log file. I suggest you set the group permissions
for whatever will be reading the logs (eg. nxlog, as shown later). Naturally,
change the path to suit your needs.

~~~
sudo /usr/sbin/useradd --system --user-group ipfix
sudo install --directory --owner ipfix --group nxlog --mode 0750 /logs/current/ipfix/
~~~

Let's see how to run it by hand. 

~~~
sudo su - ipfix
export LD_LIBRARY_PATH=/opt/libipfix/lib
/opt/libipfix/bin/ipfix_collector -4 -u --json --jsonfile /logs/current/ipfix/data.json --fallback-templates=netscaler
~~~

Log files must be rotated
===

So now we have the process running, and logging data. Logging data needs to be
rotated, so let's do that now before we forget and cause a problem later on.
Assuming that you're running logrotate, creating a log rotation policy is fairly
easy. Note that because we don't record a PID, as a proper daemon will, it may not
work if there are multiple such processes found.

~~~
# cat /etc/logrotate.d/ipfix
/logs/current/ipfix/data.json {
    nodateext
    rotate 3
    daily
    compress
    delaycompress
    postrotate
        skill -HUP -u ipfix -c ipfix_collector
    endscript
}
~~~

Note that I've specified a rather short rotation lifetime, because I'm passing
all this to nxlog, and nxlog will be looking after retention. Alter to suit
your environment and needs.

Force a rotation and check that a new file has opened. I like to make my files
in /etc/logrotate.d/ fairly standalone so I can force a rotation on a
particular policy.

~~~
logrotate -f /etc/logrotate.d/ipfix
~~~


Do something with the data
===

Where you put the file and what you do with it will depend on your use-case. I
will show you how you can use nxlog to tail the file, add some extra
information, and send it on to something like Logstash and Elasticsearch, where
you can then view it with Kibana.

Read the data with nxlog and forward it to logstash
===

Note that logstash can tail a file (I believe), but I prefer to have the data
go into nxlog, because I set nxlog the task of managing data retention, and it
will add some extra data which will help me use the data inside of the rest of
my logging system. Nothing about this program requires (or even knows about)
nxlog, or ELK. Its only assumption is that you can tail a file where each line
is a JSON document.

Here is about the simplest config for nxlog that will read the file, add some
extra data (for illustration), and send it to logstash.

~~~
<Input in_ipfix_netscalers>
    Module        im_file
    File          "/logs/current/ipfix/data.json"
    SavePos       TRUE
    ReadFromLast  TRUE
    InputType     LineBased
    Exec          parse_json(); \
                  $SITE_application_stack = "some_group_of_netscalers"; \
                  $SITE_log_type = "ipfix_appflow"; \
                  $SITE_environment = "dev"; \
                  $EventTime = parsedate($ipfix_timestamp);
</Input>

# IMPORTANT
# =========
#
# When receiving input as JSON, and then modifying it, beware that the default
# presentation of the output is the same as the input. So, if you add
# SITE_application_stack etc. to the incoming object, and then proceed to write
# it out without having first had to_json() applied to it, you will not get the
# SITE_application_stack attribute added to the outgoing JSON document; this
# messes up the message routing. So remember to apply to_json() in each output
# that is outputting JSON (and similarly for any other such output).
#
<Output out_logstash>
    Module      om_tcp
    Host        mylogstash.example.com
    Port        5140
    Exec        to_json();
</Output>

<Route route_all>
    Path  in_ipfix_netscalers => out_logstash
</Route>
~~~

From nxlog, you may not do anything further, but if you like to process things
further in the likes of logstash (eg. putting different major systems in
different sets of indexes inside Elasticsearch), then you may need something
like the followig snippets (treat these as inspiration). Before we go further,
just check your nxlog logging in case of an error.  You could even verify that
it sending data to logstash with tcpdump (assuming that tcpdump is up at the time).

~~~
tcpdump -q -p -nn -s0 -i lo -A tcp and port 5140 | grep netscalers
~~~

Here's the start of a suitable logstash configuration.

~~~
input
{
    tcp
    {
        host => "0.0.0.0"
        port => 5140
        mode => "server"
        codec => "json_lines"
    }
}

filter
{
    # We create a different index for each day, which makes removing old data
    # fairly easy. It also means that we can optimise old indexes (which we
    # shouldn't need to do unless we've deleted documents from an index), or
    # reduce the number of replicas for old data, or change where an index is
    # stored.
    #
    # Some application stacks are very heavy in terms of log volume. To
    # give us more flexibility in how we handle those indexes (such as
    # removing or reducing replica count earlier than we would otherwise),
    # we can put them into different indexes in a case-by-case basis, and
    # the rest will go into a common index.
    #
    # Note that the variable name must be lowercased in the template name
    # (and ONLY in the template name); I think it is interpreted by Elastic
    # Search, not by LogStash, and ES seems to want it lowercase.
    #
    # One symptom of the template not applying is that the .raw attributes,
    # such as username.raw, aren't available.
    #
    if [SITE_application_stack] in ["bigone", "megaone", "netscalers"]
    {
        alter
        {
            add_field =>
            {
                "site_index_basename" => "%{SITE_application_stack}"
            }
        }
    }
    else
    {
        alter
        {
            add_field =>
            {
                "site_index_basename" => "logstash"
            }
        }
    }

    date
    {
        match => ["EventTime", "YYYY-MM-dd HH:mm:ss"]
    }
}

output
{
    # Kibana 4 (up to at least beta 4) requires all nodes to be ES version 1.4.0+,
    # as it doesn't know (although the data is there) how to differentiate a
    # client node
    #
    # Doc: http://logstash.net/docs/1.4.2/outputs/elasticsearch_http
    #
    elasticsearch_http
    {
        host => "127.0.0.1"
        template_name => "%{site_index_basename}"
        index => "%{site_index_basename}-%{+YYYY.MM.dd}"
    }
}
~~~

There are other common things you could do, such as geoip lookups and user-agent breakdown, but that's well outside the scope of this document.

If you are sorting things into different groups of indexes, then you may need to do something with your templates in Elasticsearch. Access the REST interface (I suggest using the Koph plugin -- use whatever you are comfortable with) and get the template for 'logstash'.

~~~
# curl -XGET localhost:9200/_template/logstash?pretty
{
  "logstash" : {
    "order" : 0,
    "template" : "logstash-*",
    "settings" : {
      "index.refresh_interval" : "30s",
      "index.number_of_replicas" : "1"
    },
    "mappings" : {
      "_default_" : {
        "dynamic_templates" : [ {
          "string_fields" : {
            "mapping" : {
              "index" : "analyzed",
              "omit_norms" : true,
              "type" : "string",
              "fields" : {
                "raw" : {
                  "ignore_above" : 256,
                  "index" : "not_analyzed",
                  "type" : "string"
                }
              }
            },
            "match_mapping_type" : "string",
            "match" : "*"
          }
        } ],
        "properties" : {
          "geoip" : {
            "path" : "full",
            "dynamic" : true,
            "type" : "object",
            "properties" : {
              "location" : {
                "type" : "geo_point"
              }
            }
          },
          "@version" : {
            "index" : "not_analyzed",
            "type" : "string"
          }
        },
        "_all" : {
          "enabled" : true
        }
      }
    },
    "aliases" : { }
  }
}
~~~

I increase the refresh interval to about 30s for larger things (this is more efficient). Change the bit where it says "logstash-*" to be "netscalers-*", and removing the outer layering as shown, PUT the new template.

~~~
curl -XPUT localhost:9200/_template/netscalers -d '
{
  "template" : "netscalers-*",
  "settings" : {
    "index.refresh_interval" : "30s",
    "index.number_of_replicas" : "1"
  },
  "mappings" : {
    "_default_" : {
      "dynamic_templates" : [ {
        "string_fields" : {
          "mapping" : {
            "index" : "analyzed",
            "omit_norms" : true,
            "type" : "string",
            "fields" : {
              "raw" : {
                "ignore_above" : 256,
                "index" : "not_analyzed",
                "type" : "string"
              }
            }
          },
          "match_mapping_type" : "string",
          "match" : "*"
        }
      } ],
      "properties" : {
        "geoip" : {
          "path" : "full",
          "dynamic" : true,
          "type" : "object",
          "properties" : {
            "location" : {
              "type" : "geo_point"
            }
          }
        },
        "@version" : {
          "index" : "not_analyzed",
          "type" : "string"
        }
      },
      "_all" : {
        "enabled" : true
      }
    }
  },
  "aliases" : { }
}
'
~~~

NOTE: I have not attempted to optimise the mapping that this template would produce. I know there is plenty of work in that area that could be done.

Make sure you get the following output

~~~
{"acknowledged":true}
~~~

