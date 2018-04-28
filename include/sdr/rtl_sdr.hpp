#include <iostream>
#include <rtl-sdr.h>

class rtl_sdr
{
	rtlsdr_dev_t* m_device{nullptr};

	static constexpr int m_read_len{512};
	unsigned char m_read_buf[m_read_len];
	int m_n_read{0};

	bool m_is_open{false};
	bool m_read_sync{false};

public:
	~rtl_sdr()
	{
		if(m_is_open) this->close();
	}

	bool open(uint32_t index = 0)
	{
		if(rtlsdr_get_device_count() == 0)
		{
			std::cout << "Error: no devices connected." << std::endl;
			return false;
		}
		return m_is_open = (rtlsdr_open(&m_device, index) != -1);
	}

	void close()
	{
		if(!m_is_open) return;
		rtlsdr_close(m_device);
	}

	void set_center_freq(uint32_t freq)
	{
		if(!m_is_open) return;
		rtlsdr_set_center_freq(m_device, freq);
	}

	void set_sample_rate(uint32_t rate)
	{
		if(!m_is_open) return;
		rtlsdr_set_sample_rate(m_device, rate);
	}

	void read_sync() noexcept { m_read_sync = true; }

	void read_sync_stop() noexcept { m_read_sync = false; }

	const unsigned char* get_last_read_sync_data() const noexcept
	{
		return m_read_buf;
	}

	int get_last_n_read() const noexcept { return m_n_read; }

	bool is_open() const noexcept { return m_is_open; }

	void update()
	{
		if(m_read_sync)
		{
			rtlsdr_reset_buffer(m_device);
			rtlsdr_read_sync(m_device, m_read_buf, m_read_len, &m_n_read);
		}
	}
};
