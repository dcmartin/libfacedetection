#!/bin/bash

process_face_results()
{
  local json=${1}.json
  local jpeg=${1}.jpg
  local colors=(blue red white yellow green orange magenta cyan)
  local result

  if [ -s "${json}" ] && [ -s "${jpeg}" ]; then
    local length=$(jq '.results|length' ${json})
    faces=

    if [ ${length:0} -gt 0 ]; then
      local i=0
      local count=0

      while [ ${i} -lt ${length} ]; do
        local face=$(jq '.results['${i}']' ${json})
        local left=$(echo "${face:-null}" | jq -r '.x')
        local top=$(echo "${face:-null}" | jq -r '.y')
        local width=$(echo "${face:-null}" | jq -r '.width')
        local height=$(echo "${face:-null}" | jq -r '.height')
        local bottom=$((top+height))
        local right=$((left+width))
        local confidence=$(echo "${face:-null}" | jq -r '.confidence')

echo "${confidence}: ${top},${left},${bottom},${right}"

        if [ ${i} -eq 0 ]; then
          file=${jpeg%%.*}-${i}.jpg
          cp -f ${jpeg} ${file}
        else
          rm -f ${file}
          file=${output}
        fi
        output=${jpeg%%.*}-$((i+1)).jpg

        #convert -pointsize 24 -stroke ${colors[${count}]} -fill none -strokewidth 2 -draw "rectangle ${left},${top} ${right},${bottom} push graphic-context stroke ${colors[${count}]} fill ${colors[${count}]} translate ${right},${bottom} rotate 40 path 'M 10,0  l +15,+5  -5,-5  +5,-5  -15,+5  m +10,0 +20,0' translate 40,0 rotate -40 stroke none fill ${colors[${count}]} text 3,6 '${confidence}' pop graphic-context" ${file} ${output}
        convert -pointsize 16 -stroke ${colors[${count}]} -fill none -strokewidth 2 -draw "rectangle ${left},${top} ${right},${bottom} push graphic-context stroke ${colors[${count}]} fill ${colors[${count}]} translate ${right},${bottom} text 3,6 '${confidence}' pop graphic-context" ${file} ${output}

        if [ ! -s "${output}" ]; then
          echo "Failed"
          exit 1
        fi

        i=$((i+1))
        count=$((count+1))
        if [ ${count} -ge ${#colors[@]} ]; then count=0; fi
      done
      if [ ! -z "${output:-}" ]; then
        rm -f ${file}
        result=${jpeg%%.*}-face.jpg
        mv ${output} ${result}
      fi
    fi
  fi      
  echo "${result:-null}"
}


if [ ! -z "${*}" ]; then
  process_face_results ${*}
else
  echo "Usage: ${0} <sample>; for example: ${0} ea7the" &> /dev/stderr
fi
