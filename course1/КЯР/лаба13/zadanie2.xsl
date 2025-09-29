<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:template match="/ratelist">
            <html>
                <body>
                        <table border="2">
                            <tr bgcolor="skyblue">
                                <th>Студент</th>
                                <th>ОАИП</th>
                                <th>ТРПО</th>
                                <th>КЯР</th>
                                <th>СЯП</th>
                            </tr>
                            <xsl:for-each select="student">
                            <tr>
                                <td><xsl:value-of select="name"/></td>
                                <xsl:choose>
                                    <xsl:when test="grade1 &gt; 8">
                                        <td bgcolor="green"><xsl:value-of select="grade1"/></td>
                                    </xsl:when>
                                    <xsl:when test="grade1 &lt; 4">
                                        <td bgcolor="red"><xsl:value-of select="grade1"/></td>
                                    </xsl:when>
                                    <xsl:otherwise>
                                        <td><xsl:value-of select="grade1"/></td>
                                    </xsl:otherwise>
                                </xsl:choose>

                                <xsl:choose>
                                    <xsl:when test="grade2 &gt; 8">
                                        <td bgcolor="green"><xsl:value-of select="grade2"/></td>
                                    </xsl:when>
                                    <xsl:when test="grade2 &lt; 4">
                                        <td bgcolor="red"><xsl:value-of select="grade2"/></td>
                                    </xsl:when>
                                    <xsl:otherwise>
                                        <td><xsl:value-of select="grade2"/></td>
                                    </xsl:otherwise>
                                </xsl:choose>

                                 <xsl:choose>
                                    <xsl:when test="grade3 &gt; 8">
                                        <td bgcolor="green"><xsl:value-of select="grade3"/></td>
                                    </xsl:when>
                                    <xsl:when test="grade3 &lt; 4">
                                        <td bgcolor="red"><xsl:value-of select="grade3"/></td>
                                    </xsl:when>
                                    <xsl:otherwise>
                                        <td><xsl:value-of select="grade3"/></td>
                                    </xsl:otherwise>
                                </xsl:choose>
                                
                                 <xsl:choose>
                                    <xsl:when test="grade4 &gt; 8">
                                        <td bgcolor="green"><xsl:value-of select="grade4"/></td>
                                    </xsl:when>
                                    <xsl:when test="grade4 &lt; 4">
                                        <td bgcolor="red"><xsl:value-of select="grade4"/></td>
                                    </xsl:when>
                                    <xsl:otherwise>
                                        <td><xsl:value-of select="grade4"/></td>
                                    </xsl:otherwise>
                                </xsl:choose>
                            </tr>
                            </xsl:for-each>
                        </table>
                </body>
             </html>
    </xsl:template>
</xsl:stylesheet>