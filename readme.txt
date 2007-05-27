
                         WATCHANYCASTSERVERD
                     Watch anycast server daemon



PURPOSE

This software has a specific purpose -- to watch a daemon process
which is providing an anycast service. When that process ends, for
whatever reason, this software will drop carrier on a supplied list of
network interfaces.

A routing daemon advertises a route which allows the anycast service
provided by the daemon to be found. That route is orignated in a
loopback interface. When this program drops carrier on that loopback
interface the routing daemon will withdraw the route for the service
running on this machine.

This program prevents the scenario where the route for a anycast
service is being offered, but the service itself is not being offered.

This program does not test for the operation of the service
itself. That can be done by another program. Alternatively, it may be
better not to test for the operation of a service at all -- thus
isolating a denial of service attack rather than giving a DoS attack
the opportunity to attack all of the servers providing the anycast
service.

For a full tutorial on anycast services see the file
anycast-named.odf.

For the building and installation of this program see the file install.txt.

For a full technical description of the program's operation see the
troff-format manual page watchanycastdeamon.8.


THANKS

For deploying anycast services, thanks to Kim Hawtin at The University
of Adelaide and Ivan Philips, Mark Eldridge and David Jericho at
Australia's Academic & Research Network.

For the hint for using the Linux Taskstats facility, thanks to Andrew
Morton of the Linux Foundation.

For the time to write this program, thanks to my family: Karen, Kayla
and Ella.


COPIES OF THIS PROGRAM

This program and related materials can be found at
 <http://www.aarnet.edu.au/~gdt/software/watchanycastserverd/>


COPYRIGHT, LICENSE AND NO WARRANTY

Copyright © Glen David Turner of Semaphore, South Australia, 2007.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
02110-1301, USA.


$Id$
