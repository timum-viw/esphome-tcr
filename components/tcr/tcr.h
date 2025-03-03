#pragma once

#include "esphome/core/component.h"
#include "esphome/core/helpers.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/i2c/i2c.h"

using esphome::i2c::ErrorCode;

namespace esphome
{
    namespace tcr
    {
        struct __attribute__((packed)) tcr_result_t
        {
            uint16_t length;
            char content[254];
        };

        class TcrSensor : public text_sensor::TextSensor,
                          public PollingComponent,
                          public i2c::I2CDevice
        {
        public:
            void update() override
            {
                static tcr_result_t result;
                auto error = this->read((uint8_t *)&result, 128);
                if (error == ErrorCode::NO_ERROR && result.length > 0 && result.length < 255)
                {
                    result.content[result.length] = '\0';
                    if(strlen(result.content) == result.length) {
                        this->publish_state(str_sprintf("%s", result.content));
                    }
                }
            }
        };

    } // namespace tcr
} // namespace esphome