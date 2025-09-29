<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/companies">
    <html>
        <body>
            <xsl:for-each select="header">
                <h2><xsl:value-of select="header"/></h2>
             </xsl:for-each> 
            <h2> Information </h2>
            <table border="1">
                <tr bgcolor="#a1c1c5">
                    <th>Company </th>
                    <th>Since </th> 
                    <th>Location </th>
                </tr>
            <xsl:for-each select="company">
            <xsl:sort select="since" order="ascending"/>
                <tr bgcolor="#a1c1c5">
                    <td><xsl:value-of select="name"/></td>
                    <td><xsl:value-of select="since"/></td>
                    <td><xsl:value-of select="location"/></td>
                </tr>
                </xsl:for-each>
            </table>
        </body>
    </html>
</xsl:template>
</xsl:stylesheet>
